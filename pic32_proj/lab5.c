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

// === thread structures ============================================
// semaphores for controlling two threads
// for guarding the UART and for allowing stread blink control
//static struct pt_sem control_t1, control_t2, control_t6  ;
// thread control structs
// note that UART input and output are threads
static struct pt pt_tick;
// uart control threads
static struct pt pt_input, pt_output, pt_DMA_output ;
// system 1 second interval tick
int sys_time_half_seconds ;

// === RAM test data ====================================================
// some data to write
char test_data[]={2, 4, 6, 8, 10, 100, 200, 255}; // 8
char test_data2[8];

int test_addr = 0x0;
int ram_read = 0;
int adc_read = 0;

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

// === RAM commands ======================================================
// from 23LC1024 datasheet
// http://ww1.microchip.com/downloads/en/DeviceDoc/20005142C.pdf
// Default setup includes data streaming from current address
// This is used in the array read/write functions
#define RAM_WRITE_CMD (0x2000000) // top 8 bits -- 24 bits for address
#define RAM_READ_CMD  (0x3000000) // top 8 bits -- 24 bits for address
// command format consists of a read or write command ORed with a 24-bit
// address, even though the actual address is never more than 17 bits
// general procedure will be:
// Drop chip-select line
// Do a 32-bit SPI transfer with command ORed with address
// switch to 8-bit SPI mode
// Send one or more data bytes
// Raise chip-select line
//
// At 20 MHz SPI bus rate:
// Command ORed with address, plus mode change, takes 2.2 microsec
// Each byte takes 0.75 microseconds 

/* ====== MCP4822 control word =========================================
bit 15 A/B: DACA or DACB Selection bit
1 = Write to DACB
0 = Write to DACA
bit 14 ? Don?t Care
bit 13 GA: Output Gain Selection bit
1 = 1x (VOUT = VREF * D/4096)
0 = 2x (VOUT = 2 * VREF * D/4096), where internal VREF = 2.048V.
bit 12 SHDN: Output Shutdown Control bit
1 = Active mode operation. VOUT is available. ?
0 = Shutdown the selected DAC channel. Analog output is not available at the channel that was shut down.
VOUT pin is connected to 500 k???typical)?
bit 11-0 D11:D0: DAC Input Data bits. Bit x is ignored.
*/
// A-channel, 1x, active
#define DAC_config_chan_A 0b0011000000000000

// === spi bit widths ====================================================
// hit the SPI control register directly
inline void Mode16(void){  // configure SPI2 for 16-bit mode
    SPI2CONSET = 0x400;
    SPI2CONCLR = 0x800;
}
// ========
inline void Mode8(void){  // configure SPI2 for 8-bit mode
    SPI2CONCLR = 0x400;
    SPI2CONCLR = 0x800;
}
// ========
inline void Mode32(void){  // configure SPI2 for 8-bit mode
    SPI2CONCLR = 0x400;
    SPI2CONSET = 0x800;
}

// === DAC byte write =====================================================
// address between 0 and 2^17-1
// data bytes
void dac_write_byte(int data){
    int junk;
    // Channel config ORed with data
    Mode16();
    mPORTBClearBits(BIT_4);
    // write to spi2 and convert 8 bits to 12 bits
    WriteSPI2(DAC_config_chan_A | (data));
    // test for done
    while (SPI2STATbits.SPIBUSY); // wait for end of transaction
    junk = ReadSPI2(); // must always read, even if nothing useful is returned
    // set 8-bit transfer for each byte
    mPORTBSetBits(BIT_4);
    return ;
}

// === RAM byte write =====================================================
// address between 0 and 2^17-1
// data bytes
void ram_write_byte(int addr, char data){
    int junk;
    // set 32-bit transfer for read/write command ORed with
    // actual address
    Mode32();
    mPORTBClearBits(BIT_0);
    WriteSPI2(RAM_WRITE_CMD | addr); // addr not greater than 17 bits
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2(); // must always read, even if nothing useful is returned
    // set 8-bit transfer for each byte
    Mode8();
    WriteSPI2(data); // data write
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2();
    mPORTBSetBits(BIT_0);
    return ;
}

void ram_write_short(int addr, short data){
    int junk;
    // set 32-bit transfer for read/write command ORed with
    // actual address
    Mode32();
    mPORTBClearBits(BIT_0);
    WriteSPI2(RAM_WRITE_CMD | addr); // addr not greater than 17 bits
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2(); // must always read, even if nothing useful is returned
    // set 8-bit transfer for each byte
    Mode8();
    
    WriteSPI2((char)data); // data write
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2();
    
    WriteSPI2(data >> 8); // data write
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2();
    
    mPORTBSetBits(BIT_0);
    return ;
}

// === RAM array write =====================================================
// address, pointer to an array containing the data, number of BYTES to store
void ram_write_byte_array(int addr, char* data, int count){
    int junk, i;
    Mode32();
    mPORTBClearBits(BIT_0);
    WriteSPI2(RAM_WRITE_CMD | addr); // addr not greater than 17 bits
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2();
    Mode8();
    for(i=0; i<count; i++){
        WriteSPI2(data[i]); // data write
        while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
        junk = ReadSPI2();
    }
    mPORTBSetBits(BIT_0);
    return ;
}

// === RAM byte read ======================================================
int ram_read_byte(int addr){
    int junk, data;
    Mode32();
    mPORTBClearBits(BIT_0);
    WriteSPI2(RAM_READ_CMD | addr); // addr not greater than 17 bits
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2();
    Mode8();
    WriteSPI2(junk); // force the read
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    data = ReadSPI2();
    mPORTBSetBits(BIT_0);
    return data;
}

// === RAM array read ======================================================
// address, pointer to an array receiving the data, number of BYTES to read
int ram_read_byte_array(int addr, char* data, int count){
    int junk, i;
    Mode32();
    mPORTBClearBits(BIT_0);
    WriteSPI2(RAM_READ_CMD | addr); // addr not greater than 17 bits
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2();
    Mode8();
    for(i=0; i<count; i++){
        WriteSPI2(junk); // force the read
        while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
        data[i] = ReadSPI2();
    }
    mPORTBSetBits(BIT_0);
    return ;
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

#define MAX_ADDR 0x1FFFF
#define MIN_ADDR 0x00000

int w_addr = 0x0, r_addr = 0x0;
char r_valid= 0;

void __ISR(_TIMER_2_VECTOR, ipl2) Timer2Handler(void)
{
  // 74 cycles to get to this point from timer event
  mT2ClearIntFlag();
  mPORTBSetBits(BIT_0);
  adc_read = ReadADC10(0); 
  AcquireADC10();

//  ram_write_byte(test_addr, adc_read>>2);
//  ram_read = ram_read_byte(test_addr);
//  dac_write_byte(ram_read<<4);
//  test_addr++;
  
  ram_write_byte(w_addr, adc_read>>2);  
  if (r_valid) {
    ram_read = ram_read_byte(r_addr);
    dac_write_byte(ram_read<<4); // Writes to channel A
  }
  
  w_addr += 1;
  r_addr += 1;
  if (w_addr == MAX_ADDR - 1) {
    // set r_addr to MIN_ADDR
    r_addr = MIN_ADDR;
    r_valid = 1;
  }
  if (w_addr > MAX_ADDR) {
    w_addr = MIN_ADDR;
  }
  mPORTBClearBits(BIT_0);
}

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

        // TODO: READ IO
        send_byte = 0;
        send_seq = 0; // no arrow
        send_byte |= (mPORTBReadBits( BIT_7 ) == 0) << 4;
        send_byte |= (mPORTBReadBits( BIT_8 ) == 0) << 5;
        send_byte |= (mPORTBReadBits( BIT_9 ) == 0) << 6;
        send_byte |= (mPORTBReadBits( BIT_13 ) == 0) << 7;
        // 0000, 0001, 0010, 0100, 1000

        // send the prompt via DMA to serial
//        send_byte = (~send_byte) << 4;
//        sprintf(PT_send_buffer,"%d",send_byte);
        if (prev_send_time != sys_time_half_seconds) {
            send_seq = (0b11110110) & 0x0f; 
            prev_send_time = sys_time_half_seconds;
        } else {
            send_seq = 0x0f;
        }
        send_byte |= send_seq;
        PT_send_buffer[0] = send_byte;
//        PT_send_buffer[1] = '\n';
        // by spawning a print thread
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
    
  // === set up SPI =======================
  // SCK2 is pin 26 
  // SDO2 (MOSI) is in PPS output group 2, could be connected to RPB5 which is pin 14
  PPSOutput(2, RPB5, SDO2);
  // SDI2 (MISO) is PPS output group 3, could be connected to RPA2 which is pin 9
  PPSInput(3,SDI2,RPA2);

  // BIT_0 = RAM 1, BIT_1 = RAM 2, BIT_4 = DAC
  // control CS for RAM (bit 0) and for DAC (bit 1)
  mPORTBSetPinsDigitalOut(BIT_0 | BIT_4);
  //and set both bits to turn off both enables
  mPORTBSetBits(BIT_0 | BIT_4);
  
  EnablePullDownB( BIT_7 | BIT_8 | BIT_9 | BIT_13 );
  mPORTBSetPinsDigitalIn( BIT_7 | BIT_8 | BIT_9 | BIT_13 );
        
  // divide Fpb by 2, configure the I/O ports. Not using SS in this example
  // 8 bit transfer CKP=1 CKE=1
  // possibles SPI_OPEN_CKP_HIGH;   SPI_OPEN_SMP_END;  SPI_OPEN_CKE_REV
  // For any given peripherial, you will need to match these
  SpiChnOpen(
          spiChn2, 
          SPI_OPEN_ON | SPI_OPEN_MODE8 | SPI_OPEN_MSTEN | SPI_OPEN_CKE_REV, 
          spiClkDiv
    );
  
  // === now the threads ====================

  // init the threads
  PT_INIT(&pt_tick);
  PT_INIT(&pt_input);
  
  ram_write_byte_array(test_addr, test_data, 8);
  int i;
  for (i = 0; i < 0x1ffff; i += 8) {
      ram_write_byte_array(test_addr, test_data, 8);
      test_addr += 8;
  }
  test_addr = 0x0;
  w_addr = 0x0;
  r_addr = 0x0;
  
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
  }
} // main
