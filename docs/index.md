# *Dance Dance Evolution*

### Real Time Beat Detection, Audio Buffering, and User Input Using the PIC32

*Designed for ECE 4760: Digital Systems Design Using Microcontrollers*

*Drew Dunne (asd222) & Michael Solomentsev (mys29)*

---

### Background

We designed a version of the traditional arcade game 'Dance Dance Revolution' that live synthesizes dance instructions from any audio source using the PIC32. **Add more about how the project works**

We were inspired by a mutual desire to work on a music related project, and both had fond memories of playing the game as children. We also wanted to add some sort of novel, interesting component, so we brainstormed the idea of having the player be able to play whatever song they wanted. This would make the game much more captivating and engaging. All versions of the game have pre-programmed song libraries, so replay value is ultimately limited. Our version has no such limitation. 

 **INSERT PHOTO**

---

### High Level Design

The system must take in two kinds of user input: An audio source and button pushes from the floor tiles. It then must process those inputs, and display scoring and upcoming button press instructions on a screen. We use the PIC32 to do the aforementioned input processing, and use a Mac application to display the beats and handle scoring. 

For audio: We use the PIC's onboard analog to digital converter (ADC) to sample the signal from an audio jack at 44kHz. The signal is then processed in .1 second chunks (approximately 4000 samples) using a discrete wavelet transform to determine whether a beat has occurred during that time segment. Because this takes a finite amount of time, we cannot simply play the recieved signal. Rather, we delay the sound so that arrow instructions appear on the screen several seconds before the player must press those buttons. The audio is delayed using a 128KB external SRAM, which interfaces with the PIC using serial peripheral interface (SPI) communication protocol. Upon sampling, 10 bit ADC data is truncated to 8 bits and sent to the SRAM. Once the SRAM's memory has filled up, every write is accompanied by a read. The read data is sent to the PIC's digital to analog converter (DAC), where it is played by a speaker. 

For user input: The floor tiles are built using Interlink Electronics' force sensitive resistors. Each tile functions as a simple voltage divider, where voltage spikes to approximately 3V on a press. We feed the outputs of these dividers to the PIC, where we have selected four pins to act as digital inputs. We send the pressed inputs and the desired arrow instructions to the Mac via the serial port.

---

### Software Design

#### Mac App

#### Signal Processing and Beat Detection



#### Audio Buffering using External SRAM

---

### Hardware Design

We used the PIC32 big development board, because it provided the best flexibility for development. It had the DAC already on board, and a variety of pins ready for use. Since we were already running significantly under budget, we had no incentive to cut cost and move to the small board. 

####Audio Circuitry

We soldered up our audio circuitry to make it look nice and to reduce noise. This circuitry was extremely rudimentary. Our audio input jack fed into a 500uF capacitor to cut out any DC component, then we fed it in between two 10KΩ resistors sitting between 3.3V and ground to offset it, so that the ADC could read it with no clipping. The DAC output was fed directly to an audio jack and speakers.

**put a photo here!!!!**

#### Floor Tiles

The major consideration that affected our tile construction was a desire for resiliency. Since users would probably stomp on each of the tiles fairly hard, we wanted to make sure that our press detection system could withstand a whole lot of force. We also wanted a simple, easy solution to mock-up and build with minimal hardware knowledge (since our backgrounds are in ECE and CS). Initially we looked into using strain gauges, but they would require mounting to a base plate and the tile to be pushed. Traditional buttons did not seem like a robust enough option. Instead, we decided to use force sensitive resistors (FSRs). Initial testing revealed that the unpressed FSRs had resistance of approximately 6 MΩ, pressed was approximately 1KΩ. This huge discrepancy made it easy to probe it for a press. We contacted Interlink Electronics, and they were gracious enough to donate 10 FSR402s, making it possible for us to be under budget.

Because the FSRs were small in area (<1 inch square), we added two to each tile to increase the robustness of detection. We used a plywood plank as our first version of the tile, but found it to be a bit too heavy. We then used these canvas boards that were significantly lighter. We hot-glued 1/4-in nuts to each of the FSRs and placed them near the center along one diagonal of the board. We then hot-glued washers and nuts to each of the four corners. As a result of this setup, the resistors typically had no force applied to them, because they hardly rested on the floor. However, once depressed, the board bended slightly and the FSRs were squeezed. We wired the two resistors in parallel, then in series with a 10KΩ resistor. Running 3.3 V across the setup and measuring the voltage at the intersection point gave us voltage levels of basically 0V/3.2V when unpressed/pressed, which meant we could just wire up each tile to a digital pin.

![alt text](resources/tile1.JPG "First Tile")

*Our First Tile*

---

### Results

#### Speed

####Safety

#### Usability

---

###Conclusions

#### ADD: did we accomplish our goals?

Our project is heavily inspired by the game Dance Dance Revolution, which is indeed a trademarked property. The title 'Dance Dance Evolution' is not trademarked at all, however. In a sense, we did reverse engineer the mechanics of their game, but we could not find a specific patent for the game play mechanism. We do not think our beat detection algorithm/approach is novel enough to patent (see the Tzanetakis paper in our references). We reuse some code written by Bruce Land and Tahmid Mahmud for the course. Since our project is entirely open source and we are not seeking to mass-produce this for profit, we do not think we are violating any intellectual property.

We believe that our project is fully compliant with IEEE standards. We embarked on the project in an effort to bring an enjoyable, fun game to the masses, and that is ultimately what we ended up doing. Our project's individual components are all harmless: Floor switches, audio buffering, and beat detection. We made special effort to make sure individuals do not trip or injure their feet when playing the game by putting the tiles low to the ground and making sure they would not slide around. As noted above, we do not think we are making any IP violations through the project. Even if our interpretation of the law is incorrect, we doubt that the publication of a single open source version of the Dance Dance Revolution game will cause the game publishers to lose any income. By making our code, schematics, and methodology publically available, we hope to encourage understanding of technology and spark interest in embedded design and signal processing, as per point five of the IEEE Code of Ethics. Moreover, we have noted all contributors and sources of code and ideas. In summation: Our project is fairly benign, and we hope it brings joy to all who play it.

We found no legal issues with our project.

---

### Acknowledgements

We would like to heartily thank Interlink Electronics for their generous donation of 10 force sensitive resistors (part number FSR402). Their contribution made our project possible.

In addition, we are extremely grateful to Professor Bruce Land, who provided an immeasurable amount of help. Big thanks also to Professor David Delchamps, whose lectures and advice inspired the signal analysis component of our project. Mark Zhao was a spectacular, well-informed TA.

---

### Appendix A: Permissions

The group approves this report for inclusion on the course website.

The group approves the video for inclusion on the course Youtube channel.

---

### Appendix B: Commented Code

should put links to other pages/github here

---

###Appendix C: Schematics

---

### Appendix D: Budgeting

| Part                               | Quantity | Cost   |
| ---------------------------------- | :------- | ------ |
| Force Sensitive Resistors (FSR402) | 10       | $0.00  |
| Auxillary Audio Cord               | 1        | $1.74  |
| 10"x10" Canvas Boards              | 5        | $10.00 |
| PIC32 Large Development Board      | 1        | $10.00 |
| Serial to Serial Cable             | 1        | $5.00  |
| 1/4" 20 Hex Nuts                   | 28       |        |
| Jumper Cables                      | ???      |        |
| 6" Solder Board                    | 1        | $2.50  |
| 2" Solder Board                    | 1        | $1.00  |
| 9V Power Supply                    | 1        | $5.00  |
| Lab Speakers                       | 1        | $2.00  |
| Header Sockets                     | 1        |        |
| PIC32MX250F128B                    | 1        | $5.00  |
| 23LC1024 SRAM                      | 1        |        |
|                                    |          |        |
| **TOTAL**                          |          | $37.24 |

---

###Appendix E: Work Distribution

Drew focused on:

* Serial communications
* Getting the SRAM to work
* Buffering audio
* Data transfer between PIC and Mac
* Writing the Mac app

Michael focused on:

* Prototyping and building all the floor tiles
* Soldering protoboards
* Testing and modeling wavelet transforms in MATLAB
* Finding and working with a suitable DWT library
* Writing C implementation of beat detection

---

###Appendix F: References and Helpful Resources

[George Tzanetakis' wonderful paper on beat extraction with the discrete wavelet transform](http://soundlab.cs.princeton.edu/publications/2001_amta_aadwt.pdf)

[Rafat Hussain's C Wave Library, which we didn't end up using, but may be a helpful resource](https://github.com/rafat/wavelib)

[The GNU Scientific Library](https://github.com/ampl/gsl)

[Datasheet for Interlink FSR402](http://interlinkelectronics.com/datasheets/Datasheet_FSR.pdf)

[PIC32 Peripheral Library AKA The Holy Bible](http://ww1.microchip.com/downloads/en/DeviceDoc/32bitPeripheralLibraryGuide.pdf)

[IEEE Code of Ethics](https://www.ieee.org/about/corporate/governance/p7-8.html)

**TWO THINGS TO ADD: SPOTIFY PLAYLIST AND LINK TO OUR GITHUB**