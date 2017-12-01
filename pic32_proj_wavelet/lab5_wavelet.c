/*********************************************************************
 *
 *                  SPI to  23LC1024 serial RAM & DAC
 * Uses interactive commands from the uart to test SPI serial RAM
 * Same SPI channel is used to drive DAC
 *
 *********************************************************************
 * Bruce Land -- Cornell University
 * Dec 2015
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

//=== clock AND protoThreads configure =============================
#include "config.h"
// threading library
#include "pt_cornell_1_2_1.h"
#include <stdlib.h>
#include <math.h>
#include "gsl_wavelet.h"

// === thread structures ============================================
// semaphores for controlling two threads
// for guarding the UART and for allowing stread blink control
//static struct pt_sem control_t1, control_t2, control_t6  ;
// thread control structs
// note that UART input and output are threads
static struct pt pt_tick, pt_proc;
// uart control threads
static struct pt pt_input, pt_output, pt_DMA_output ;
// system 1 second interval tick
int sys_time_half_seconds ;

//---------Pull Down Resistors---------
// PORT B
#define EnablePullDownB(bits) CNPUBCLR=bits; CNPDBSET=bits;
#define DisablePullDownB(bits) CNPDBCLR=bits;
#define EnablePullUpB(bits) CNPDBCLR=bits; CNPUBSET=bits;
#define DisablePullUpB(bits) CNPUBCLR=bits;
//PORT A
#define EnablePullDownA(bits) CNPUACLR=bits; CNPDASET=bits;
#define DisablePullDownA(bits) CNPDACLR=bits;
#define EnablePullUpA(bits) CNPDACLR=bits; CNPUASET=bits;
#define DisablePullUpA(bits) CNPUACLR=bits;

// === SPI setup ========================================================
volatile SpiChannel spiChn2 = SPI_CHANNEL2 ;	// the SPI channel to use
volatile int spiClkDiv = 2 ; // 20 MHz max speed for this RAM

// inclusive low to exclusive high
int absmax(int *array, int l, int h) {
  int max;
  int i;
  int a;

  max = 0;
  for (i = l; i < h; ++i) {
    a = abs(array[i]);
    if (a > max)
      max = a;
  }

  return max;
}

// === Thread 5 ======================================================
// update a 1 second tick counter
static PT_THREAD (protothread_tick(struct pt *pt))
{
    PT_BEGIN(pt);

      while(1) {
            // yield time 1 second
            PT_YIELD_TIME_msec(1000) ;
            sys_time_half_seconds++ ;
            // NEVER exit while
      } // END WHILE(1)
  PT_END(pt);
} // thread 4

inline void setup_adc(void) {
  /////////////////// ADC //////////////////////
  // configure and enable the ADC
  CloseADC10();	// ensure the ADC is off before setting the configuration

  // define setup parameters for OpenADC10
  // Turn module on | ouput in integer | trigger mode auto | enable autosample
  // ADC_CLK_AUTO -- Internal counter ends sampling and starts conversion (Auto convert)
  // ADC_AUTO_SAMPLING_ON -- Sampling begins immediately after last conversion completes; SAMP bit is automatically set
  // ADC_AUTO_SAMPLING_OFF -- Sampling begins with AcquireADC10();
  #define PARAM1  ADC_FORMAT_INTG16 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON //

  // define setup parameters for OpenADC10
  // ADC ref external  | disable offset test | disable scan mode | do 1 sample | use single buf | alternate mode off
  #define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_2 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_ON

  // Define setup parameters for OpenADC10
  // use peripherial bus clock | set sample time | set ADC clock divider
  // ADC_CONV_CLK_Tcy2 means divide CLK_PB by 2 (max speed)
  // ADC_SAMPLE_TIME_5 seems to work with a source resistance < 1kohm
  #define PARAM3 ADC_CONV_CLK_PB | ADC_SAMPLE_TIME_5 | ADC_CONV_CLK_Tcy2

  // define setup parameters for OpenADC10
  // set AN5 and  as analog inputs
  #define PARAM4	ENABLE_AN5_ANA // pin 7

  // define setup parameters for OpenADC10
  // do not assign channels to scan
  #define PARAM5	SKIP_SCAN_ALL

  // use ground as neg ref for A | use AN5 for input A     
  // configure to sample AN5 
  SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN5 ); 
  OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4, PARAM5 ); // configure ADC using the parameters defined above

  EnableADC10(); // Enable the ADC
  /////////////////////////////////////////////
}

short adc_read = 0;

#define SAMPLE_SIZE   2048
static const unsigned short SAMPLE_SIZE_2 = 2 * SAMPLE_SIZE;

short samples[SAMPLE_SIZE];
size_t sample_num = 0; // MAX is 4096
volatile char samples_full = 0;

int data[SAMPLE_SIZE];
int scratch[SAMPLE_SIZE];

static gsl_wavelet wave;
gsl_wavelet *w = &wave;

static gsl_wavelet_workspace workspace = { scratch, 2048 };
gsl_wavelet_workspace *work = &workspace;

void __ISR(_TIMER_2_VECTOR, ipl2) Timer2Handler(void)
{
  // 74 cycles to get to this point from timer event
  mT2ClearIntFlag();

  adc_read = ReadADC10(0);
  AcquireADC10();
  
  if ((sample_num & 0b1) == 0) {
    // should write to sample array
    samples[(sample_num >> 2)] = adc_read;
    
    if (++sample_num > SAMPLE_SIZE_2) {
      sample_num = 0;
      int i;
      for (i = 0; i < SAMPLE_SIZE; i++)
        data[i] = (int)samples[i];
      samples_full = 1;
      mPORTBSetBits( BIT_8 );
    }
  } else {
    sample_num++;
  }
}

volatile char should_send = 0;
volatile char arrows_to_send = 0x0;

#define CD1_THRESHOLD  750
#define CD2_THRESHOLD 1800
#define CD3_THRESHOLD 1800
#define CD4_THRESHOLD 1500
#define CD5_THRESHOLD 1500
#define CD6_THRESHOLD 1000
#define CD7_THRESHOLD  600
#define CD8_THRESHOLD  400

// === Thread 5 ======================================================
// update a 1 second tick counter
static PT_THREAD (protothread_proc(struct pt *pt))
{
  PT_BEGIN(pt);
  int i;
  char cd1_beat, cd2_beat, cd3_beat, cd4_beat, 
          cd5_beat, cd6_beat, cd7_beat, cd8_beat;
  while(1) {
    PT_WAIT_UNTIL(pt, samples_full);
    
    samples_full = 0;
    // Init wavelet and perform wavelet transform
    gsl_wavelet_alloc (w, gsl_wavelet_haar, 2);
    gsl_wavelet_transform_forward (w, data, 1, SAMPLE_SIZE, work);

    cd1_beat  = absmax(data,   2,   4) >= CD1_THRESHOLD;
    cd2_beat  = absmax(data,   4,   8) >= CD2_THRESHOLD;
    cd3_beat  = absmax(data,   8,  16) >= CD3_THRESHOLD;
    cd4_beat  = absmax(data,  16,  32) >= CD4_THRESHOLD;
    cd5_beat  = absmax(data,  32,  64) >= CD5_THRESHOLD;
    cd6_beat  = absmax(data,  64, 128) >= CD6_THRESHOLD;
    cd7_beat  = absmax(data, 128, 256) >= CD7_THRESHOLD;
    cd8_beat  = absmax(data, 256, 512) >= CD8_THRESHOLD;
    
    // Arrow generation
    arrows_to_send = 0;
    arrows_to_send |= (!(cd1_beat || cd2_beat)) << 0;
    arrows_to_send |= (!(cd3_beat || cd4_beat)) << 1;
    arrows_to_send |= (!(cd5_beat || cd6_beat)) << 2;
    arrows_to_send |= (!(cd7_beat || cd8_beat)) << 3;
    
    if (arrows_to_send != 0b00001111) should_send = 1;

    // NEVER exit while
  } // END WHILE(1)
  PT_END(pt);
} // thread 4

int prev_send_time = 0;

// === Thread 5 ======================================================
// update a 1 second tick counter
static PT_THREAD (protothread_input(struct pt *pt))
{
    PT_BEGIN(pt);
    char send_byte;
    char send_seq;
    while(1) {
        // yield time 1 second
        PT_YIELD_TIME_msec(60) ;

        send_byte = 0;
        send_seq = 0; // no arrow
        send_byte |= (mPORTBReadBits( BIT_7 ) == 0) << 4;
        send_byte |= (mPORTBReadBits( BIT_8 ) == 0) << 5;
        send_byte |= (mPORTBReadBits( BIT_9 ) == 0) << 6;
        send_byte |= (mPORTBReadBits( BIT_13 ) == 0) << 7;
        // 0000, 0001, 0010, 0100, 1000

        // send the prompt via DMA to serial
        send_seq = 0x0f;
        if (should_send) {
          send_seq = arrows_to_send; 
          should_send = 0;
        }
        send_byte |= send_seq;
        
        // by spawning a print thread
        PT_send_buffer[0] = send_byte;
        PT_SPAWN(pt, &pt_DMA_output, PT_DMA_PutSerialBuffer(&pt_DMA_output) );
        
        // NEVER exit while
    } // END WHILE(1)
    PT_END(pt);
} // thread 4

// === Main  ======================================================
// set up UART, threads
// then schedule them as fast as possible

int main(void)
{
  // === config the uart, DMA, vref, timer5 ISR =====
  PT_setup();

   // === setup system wide interrupts  =======
  INTEnableSystemMultiVectoredInt();
  
  setup_adc();
  
  EnablePullDownB( BIT_7 | BIT_8 | BIT_9 | BIT_13 );
  mPORTBSetPinsDigitalIn( BIT_7 | BIT_8 | BIT_9 | BIT_13 );
  
  // === now the threads ====================

  // init the threads
  PT_INIT(&pt_tick);
  PT_INIT(&pt_input);
  PT_INIT(&pt_proc);
  
  /////////////////TIMER SETUP/////////////
  int adc_read_ram_write_period = 1000;
  //adc_read_ram_write_period = 40000;
  OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_1, adc_read_ram_write_period);
  // set up the timer interrupt with a priority of 2
  ConfigIntTimer2(T2_INT_ON | T2_INT_PRIOR_1);
  mT2ClearIntFlag(); // and clear the interrupt flag
  /////////////////////////////////////////
        
  // schedule the threads
  while(1) {
    // round robin
    PT_SCHEDULE(protothread_tick(&pt_tick));
    PT_SCHEDULE(protothread_input(&pt_input));
    PT_SCHEDULE(protothread_proc(&pt_proc));
  }
} // main
