
#include "spi_ram_dac.h"

// === SPI setup ========================================================
volatile SpiChannel spiChn1 = SPI_CHANNEL1 ;	// the SPI channel to use
volatile SpiChannel spiChn2 = SPI_CHANNEL2 ;	// the SPI channel to use
volatile int spiClkDiv = 2 ; // 20 MHz max speed for this RAM

// === spi bit widths ====================================================
// hit the SPI control register directly
inline void SPI1_Mode16(void){  // configure SPI2 for 16-bit mode
    SPI1CONSET = 0x400;
    SPI1CONCLR = 0x800;
}
// ========
inline void SPI1_Mode8(void){  // configure SPI2 for 8-bit mode
    SPI1CONCLR = 0x400;
    SPI1CONCLR = 0x800;
}
// ========
inline void SPI1_Mode32(void){  // configure SPI2 for 8-bit mode
    SPI1CONCLR = 0x400;
    SPI1CONSET = 0x800;
}

inline void SPI2_Mode16(void){  // configure SPI2 for 16-bit mode
    SPI2CONSET = 0x400;
    SPI2CONCLR = 0x800;
}
// ========
inline void SPI2_Mode8(void){  // configure SPI2 for 8-bit mode
    SPI2CONCLR = 0x400;
    SPI2CONCLR = 0x800;
}
// ========
inline void SPI2_Mode32(void){  // configure SPI2 for 8-bit mode
    SPI2CONCLR = 0x400;
    SPI2CONSET = 0x800;
}

// === DAC byte write =====================================================
// address between 0 and 2^17-1
// data bytes
inline void dac_write_short(const int data) {
    int junk;
    // Channel config ORed with data
    SPI2_Mode16();
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
void ram_write_short(int addr, char data){
    int junk;
    // set 32-bit transfer for read/write command ORed with
    // actual address
    SPI1_Mode32();
    mPORTBClearBits(BIT_1);
    WriteSPI1(RAM_WRITE_CMD | addr); // addr not greater than 17 bits
    while (SPI1STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI1(); // must always read, even if nothing useful is returned
    // set 8-bit transfer for each byte
    SPI1_Mode8();
    WriteSPI1(data); // data write
    while (SPI1STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI1();
    mPORTBSetBits(BIT_1);
    return ;
}

// === RAM array write =====================================================
// address, pointer to an array containing the data, number of BYTES to store
void ram_write_byte_array(int addr, char* data, int count){
    int junk, i;
    SPI1_Mode32();
    mPORTBClearBits(BIT_1);
    WriteSPI1(RAM_WRITE_CMD | addr); // addr not greater than 17 bits
    while (SPI1STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI1();
    SPI1_Mode8();
    for(i=0; i<count; i++){
        WriteSPI1(data[i]); // data write
        while (SPI1STATbits.SPIBUSY); // wait for it to end of transaction
        junk = ReadSPI1();
    }
    mPORTBSetBits(BIT_1);
    return ;
}

// === RAM byte read ======================================================
int ram_read_short(int addr){
    int junk, data;
    SPI1_Mode32();
    mPORTBClearBits(BIT_1);
    WriteSPI1(RAM_READ_CMD | addr); // addr not greater than 17 bits
    while (SPI1STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI1();
    SPI1_Mode8();
    WriteSPI1(junk); // force the read
    while (SPI1STATbits.SPIBUSY); // wait for it to end of transaction
    data = ReadSPI1();
    mPORTBSetBits(BIT_1);
    return data;
}

inline void spi_ram_dac_setup() {
  // === set up SPI =======================
  // SCK2 is pin 26 
  // SDO2 (MOSI) is in PPS output group 2, could be connected to RPB5 which is pin 14
  PPSOutput(2, RPB5, SDO2);
  // SDI2 (MISO) is PPS output group 3, could be connected to RPA2 which is pin 9
  PPSInput(3, SDI2, RPA2);
  
  // SPI channel 1
  PPSOutput(2, RPB11, SDO1); // SDO1 (MOSI) to RPB11 (pin 22)
  PPSInput(2, SDI1, RPA1); // SDI1 (MISO) to RPA1 (pin 3)

  // BIT_0 = RAM 1, BIT_1 = RAM 2, BIT_4 = DAC
  // control CS for RAM (bit 0) and for DAC (bit 1)
  mPORTBSetPinsDigitalOut(BIT_0 | BIT_1 | BIT_4);
  //and set both bits to turn off both enables
  mPORTBSetBits(BIT_0 | BIT_1 | BIT_4);
  
  SpiChnOpen(
          spiChn1, 
          SPI_OPEN_ON | SPI_OPEN_MODE8 | SPI_OPEN_MSTEN | SPI_OPEN_CKE_REV, 
          spiClkDiv
    );
        
  // divide Fpb by 2, configure the I/O ports. Not using SS in this example
  // 8 bit transfer CKP=1 CKE=1
  // possibles SPI_OPEN_CKP_HIGH;   SPI_OPEN_SMP_END;  SPI_OPEN_CKE_REV
  // For any given peripherial, you will need to match these
  SpiChnOpen(
          spiChn2, 
          SPI_OPEN_ON | SPI_OPEN_MODE8 | SPI_OPEN_MSTEN | SPI_OPEN_CKE_REV, 
          spiClkDiv
    );
  
}