# Dance Dance Evolution

### Real Time Beat Detection, Audio Buffering, and User Input Using the PIC32

*Designed for ECE 4760: Digital Systems Design Using Microcontrollers*

*Drew Dunne (asd222) & Michael Solomentsev (mys29)*



### Background

We designed a version of the traditional arcade game 'Dance Dance Revolution' that live synthesizes dance instructions from any audio source using the PIC32. **Add more about how the project works**

We were inspired by a mutual desire to work on a music related project, and both had fond memories of playing the game as children. We also wanted to add some sort of novel, interesting component, so we brainstormed the idea of having the player be able to play whatever song they wanted. This would make the game much more captivating and engaging. All versions of the game have pre-programmed song libraries, so replay value is ultimately limited. Our version has no such limitation. 

 **INSERT PHOTO**

### High Level Design

The system must take in two kinds of user input: An audio source and button pushes from the floor tiles. It then must process those inputs, and display scoring and upcoming button press instructions on a screen. We use the PIC32 to do the aforementioned input processing, and use a Mac application to display the beats and handle scoring. 

For audio: We use the PIC's onboard analog to digital converter (ADC) to sample the signal from an audio jack at 44kHz. The signal is then processed in .1 second chunks (approximately 4000 samples) using a discrete wavelet transform to determine whether a beat has occurred during that time segment. Because this takes a finite amount of time, we cannot simply play the recieved signal. Rather, we delay the sound so that arrow instructions appear on the screen several seconds before the player must press those buttons. The audio is delayed using a 128KB external SRAM, which interfaces with the PIC using serial peripheral interface (SPI) communication protocol. Upon sampling, 10 bit ADC data is truncated to 8 bits and sent to the SRAM. Once the SRAM's memory has filled up, every write is accompanied by a read. The read data is sent to the PIC's digital to analog converter (DAC), where it is played by a speaker. 

For user input: The floor tiles are built using Interlink Electronics' force sensitive resistors. Each tile functions as a simple voltage divider, where voltage spikes to approximately 3V on a press. We feed the outputs of these dividers to the PIC, where we have selected four pins to act as digital inputs. We send 



### Software Design

#### Mac App

#### Signal Processing and Beat Detection

#### Audio Buffering using External SRAM



### Hardware Design

#### Floor Mat



### Results

#### Speed

####Safety

#### Usability



###Conclusions

#### Standards

#### IP Considerations

#### Ethical Considerations

#### Legal Considerations



### Acknowledgements

We would like to heartily thank Interlink Electronics for their generous donation of 10 force sensitive resistors (part number FSR402). Their contribution made our project possible.

In addition, we are extremely grateful to Professor Bruce Land, who provided an immeasurable amount of help. Big thanks to Professor David Delchamps, whose lectures and advice inspired the signal analysis component of our project. Mark Zhao was a wonderful TA.



### Appendix A: Permissions

The group approves this report for inclusion on the course website.

The group approves the video for inclusion on the course Youtube channel.



### Appendix B: Commented Code

###Appendix C: Schematics

### Appendix D: Budgeting

###Appendix E: Work Distribution

###Appendix F: References and Helpful Resources