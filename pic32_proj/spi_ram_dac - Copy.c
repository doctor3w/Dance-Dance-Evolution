
#include "spi_ram_dac.h"

// === SPI setup ========================================================
volatile SpiChannel spiChn1 = SPI_CHANNEL1 ;	// the SPI channel to use
volatile SpiChannel spiChn2 = SPI_CHANNEL2 ;	// the SPI channel to use
volatile int spiClkDiv = 2 ; // 20 MHz max speed for this RAM

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

volatile char ram_write_open_flg = 0;

inline void ram_write_open(const int cs, const int addr) {
  int junk;
  Mode32();
  mPORTBClearBits(cs);
  WriteSPI1(RAM_WRITE_CMD | addr); // addr not greater than 17 bits
  while (SPI1STATbits.SPIBUSY); // wait for it to end of transaction
  junk = ReadSPI1();
  Mode16(); // Leave in byte mode
  ram_write_open_flg = 1;
}

inline void ram_write(const short data) {
  if (ram_write_open_flg) {
    int junk;
    WriteSPI1(data); // data write
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI1();
  }
}

inline void ram_write_close(const int cs) {
  if (ram_write_open_flg) {
    mPORTBSetBits(cs);
    ram_write_open_flg = 0;
  }
}

inline void ram_write_open2(const int cs, const int addr) {
  int junk;
  Mode32();
  mPORTBClearBits(cs);
  WriteSPI2(RAM_WRITE_CMD | addr); // addr not greater than 17 bits
  while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
  junk = ReadSPI2();
  Mode16(); // Leave in byte mode
  ram_write_open_flg = 1;
}

inline void ram_write2(const short data) {
  if (ram_write_open_flg) {
    int junk;
    WriteSPI2(data); // data write
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2();
  }
}

inline void ram_write_close2(const int cs) {
  if (ram_write_open_flg) {
    mPORTBSetBits(cs);
    ram_write_open_flg = 0;
  }
}

volatile char ram_read_open_flag = 0;

inline void ram_dac_write_open(const int ram_cs, const int addr) {
  int junk;
  Mode32();
  mPORTBClearBits(ram_cs);
  WriteSPI2(RAM_READ_CMD | addr); // addr not greater than 17 bits
  while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
  junk = ReadSPI2();
  Mode16(); // Leave in byte mode
  ram_read_open_flag = 1;
}

volatile short prev_read = 0;

inline void ram_dac_write() {
  if (ram_read_open_flag) {
    mPORTBClearBits( BIT_4 ); // clear DAC CS
    WriteSPI2(prev_read); // data write
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    prev_read = ReadSPI2();
    mPORTBSetBits( BIT_4 ); // clear DAC CS
  }
}

inline void ram_dac_write_close(const int cs) {
  if (ram_read_open_flag) {
    mPORTBSetBits(cs);
    ram_read_open_flag = 0;
  }
}

inline void ram_read_open(const int ram_cs, const int addr) {
  int junk;
  Mode32();
  mPORTBClearBits(ram_cs);
  WriteSPI2(RAM_READ_CMD | addr); // addr not greater than 17 bits
  while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
  junk = ReadSPI2();
  Mode16(); // Leave in byte mode
  ram_read_open_flag = 1;
}

inline int ram_read() {
  int junk;
  if (ram_read_open_flag) {
    WriteSPI2(junk); // data write
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2();
    return junk;
  }
}

inline void ram_read_close(const int cs) {
  if (ram_read_open_flag) {
    mPORTBSetBits(cs);
    ram_read_open_flag = 0;
  }
}

void ram_write_byte_cs(int cs, int addr, char data){
    int junk;
    // set 32-bit transfer for read/write command ORed with
    // actual address
    Mode32();
    mPORTBClearBits(cs);
    WriteSPI2(RAM_WRITE_CMD | addr); // addr not greater than 17 bits
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2(); // must always read, even if nothing useful is returned
    // set 8-bit transfer for each byte
    Mode8();
    WriteSPI2(data); // data write
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2();
    mPORTBSetBits(cs);
    return ;
}

int ram_read_byte_cs(int cs, int addr){
    int junk, data;
    Mode32();
    mPORTBClearBits(cs);
    WriteSPI2(RAM_READ_CMD | addr); // addr not greater than 17 bits
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2();
    Mode8();
    WriteSPI2(junk); // force the read
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    data = ReadSPI2();
    mPORTBSetBits(cs);
    return data;
}

// === RAM byte read ======================================================
int ram_read_short(int cs, int addr){
    int junk, data;
    Mode32();
    mPORTBClearBits(cs);
    WriteSPI2(RAM_READ_CMD | addr); // addr not greater than 17 bits
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    junk = ReadSPI2();
    Mode16();
    WriteSPI2(junk); // force the read
    while (SPI2STATbits.SPIBUSY); // wait for it to end of transaction
    data = ReadSPI2();
    mPORTBSetBits(cs);
    return data;
}

// === DAC byte write =====================================================
// address between 0 and 2^17-1
// data bytes
void dac_write_short(int data) {
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

// === DAC byte write =====================================================
// address between 0 and 2^17-1
// data bytes
void dac_write_byte(int data) {
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