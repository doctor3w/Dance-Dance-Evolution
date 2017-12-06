# *Dance Dance Evolution*

### Real Time Beat Detection, Audio Buffering, and User Input Using the PIC32

*Designed for ECE 4760: Digital Systems Design Using Microcontrollers*

*Drew Dunne (asd222) & Michael Solomentsev (mys29)*

---

### Background

We designed a version of the traditional arcade game 'Dance Dance Revolution' that synthesizes dance instructions from any audio source using the PIC32. Unlike the original game where you must select from a pre-chosen listing of songs, our device allows one to plug in audio of choice. The arrow instructions are then generated in real-time by buffering the audio and processing it using the discrete wavelet transform before putting the arrows on screen.

We were inspired by a mutual desire to work on a music related project, and both had fond memories of playing the game. We also wanted to add some sort of novel, interesting component, so we brainstormed the idea of having the player be able to play whatever song they wanted. This would make the game much more captivating and engaging. All versions of the game have pre-programmed song libraries, so replay value is ultimately limited. Our version has no such limitation. We used the discrete wavelet transform to efficiently analyze different frequency components of the signal at a discrete point in time. 

 **INSERT PHOTO**

---

### High Level Design

The system requires two kinds of user input: An audio source and button pushes from the floor tiles. It then must process those inputs, delay those inputs until processing is done, and display scoring and upcoming button press instructions on a screen. We use two PIC32s to do the aforementioned input processing (one detects beats and reads the dance mat input, the other buffers audio), and we use a macOS application to display the beats and handle scoring. 

#### Audio Input

We use each of the PIC32s' onboard analog to digital converter (ADC) to sample the signal from an audio jack at 40kHz. The signal is then processed on one PIC in 100 millisecond chunks (approximately 4000 samples) using a discrete wavelet transform (DWT) to determine whether a beat has occurred during that time segment. Because this takes a finite amount of time, we cannot simply play the recieved signal. Rather, we delay the sound using the other PIC and SRAM chip so that arrow instructions appear on the screen approximately 2.4 seconds before the player must press those buttons. The audio is delayed using a 128KB external SRAM, which interfaces with the PIC using serial peripheral interface (SPI) communication protocol. Upon sampling, 10 bit ADC data is truncated to 8 bits and sent to the SRAM. Once the SRAM's memory has filled up, every write is accompanied by a read. The read data is sent to the PIC's digital to analog converter (DAC), where it is played by a speaker. It was necessary to use two PIC32s because we simply did not have enough processing power on a single PIC to handle both buffering and signal processing. Interfacing with the SRAM chip at 40kHz took 60-75% of our CPU, and to try and process that data and have well-timed dance mat input reads was too much to squeeze into one PIC32. 

#### Beat Detection

TODO: EXPLAIN THE MATH

#### Dance Mat User Input

The floor tiles are built using Interlink Electronics' force sensitive resistors, where we have to resistors per tile (in parallel). Each tile functions as a simple voltage divider, where voltage spikes to approximately 3V on a press. We feed the outputs of these dividers to the PIC, where we have selected four pins to act as digital inputs. We send the pressed inputs and the desired arrow instructions to the Mac via UART. The PIC polls the dance mat for input approximately every 60 milliseconds. 

TODO: INCLUDE SCHEMATIC OF FLOOR TILES

#### macOS Application (Display)

Rather than building any sort of display, we chose to make an app for a Mac computer, so that it was easy to plug our device in and start playing. The Mac is connected by USB with a UART serial to USB cable (LINK HERE). The application is responsible for reading arrow sequences and currently pressed arrows from the PIC and displaying that accordingly. New sequences are added to the bottom of the screen, where they gradually move up to the top. At the top are faded outline arrows, which when they are pressed on the mat, they become fully opaque. The application is responsible for determining if the user properly presses the correct arrows at the time the current arrow sequence is passing by. The user recieves points depending on how well they time their presses.

TODO: Include figure of mac display with breakdown

---

### Software Design

#### macOS Application

As mentioned before, our Mac app reads from the PIC through UART. In order to achieve this we first had to install a driver to the specific serial cable bought for the project. We used one from Prolific, the link to the driver is [here](http://www.prolific.com.tw/US/ShowProduct.aspx?p_id=229&pcid=41). Once we could communicate to the PIC over UART, we needed the Mac application to be able to communicate through UART as well, and for that we used a framework called [ORSSerialPort](https://github.com/armadsen/ORSSerialPort). This framework allowed us to use a common pattern in Cocoa development called the delegate pattern. We used ORSSerialPort to create a serial port object, which we set our app's view controller as the delegate for, and then an interface function implemented as part of the delegate pattern would be called every time there was new data to read. This made reading from the PIC very simple, as each time that method was called we knew more information had been sent from the PIC. 

The application also displayed the arrow sequences and user input, and this was done by adapting the simple Core Animation game library developed by Matt Gallagher. This library offers simple game objects, centralized game data, and CoreAnimation layers for the game objects all synchronized with NSTimers and Key-Value Observation. The game data starts a timer upon a new game which calls update functions for each game object currently in the data. Each time they object updates its properties, they value change notifies the game objects attached CoreAnimation layer object to update on the screen. The library was adapted for our arrow objects and the game data now sets a new game up with outline arrows and a score of zero. We also modified how objects were removed from the screen by using CATransactions rather than abruptly removing it, which was causing an odd lag as the arrows moved upwards. 

To combine the game view and the reading of the serial input, we had a view controller. Our app used another common Cocoa modeling called MVC, or Model-View-Controller. This idea keeps the model, or data, from interacting directly with the view. The controller handles the interaction between the two. Thus our controller would be the one reading from the serial port, and each time a byte had been sent from the PIC, it would parse those bits for the new arrow sequence as well as the currently pressed arrows. 

#### Signal Processing and Beat Detection

The idea to use wavelet transforms came from ECE3250 (Mathematics of Signal and System Analysis), where Professor Delchamps discussed the topic briefly. As an overview - wavelet transforms are a way to quickly assess the frequency of components of a signal with a degree of time resolution. The wavelet  

#### Audio Buffering using External SRAM

drew can you get this?

---

### Hardware Design

We used the PIC32 big development board, because it provided the best flexibility for development. It had the DAC already on board, and a variety of pins ready for use. Since we were already running significantly under budget, we had no incentive to cut cost and move to the small board. 

####Audio Circuitry

We soldered up our audio circuitry to make it look nice and to reduce noise. This circuitry was extremely rudimentary. Our audio input jack fed into a 500uF capacitor to cut out any DC component, then we fed it in between two 10KΩ resistors sitting between 3.3V and ground to offset it, so that the ADCs could read it with no clipping. The DAC output was fed directly to an audio jack and speakers.

**put a photo here!!!!**

#### Floor Tiles

The major consideration that affected our tile construction was a desire for resiliency. Since users would probably stomp on each of the tiles fairly hard, we wanted to make sure that our press detection system could withstand a whole lot of force. We also wanted a simple, easy solution to mock-up and build with minimal hardware knowledge (since our backgrounds are in ECE and CS). Initially we looked into using strain gauges, but they would require mounting to a base plate and the tile to be pushed. Traditional buttons did not seem like a robust enough option. Instead, we decided to use force sensitive resistors (FSRs). Initial testing revealed that the unpressed FSRs had resistance of approximately 6 MΩ, pressed was approximately 1KΩ. This huge discrepancy made it easy to probe it for a press. We contacted Interlink Electronics, and they were gracious enough to donate 10 FSR402s, making it possible for us to be under budget.

Because the FSRs were small in area (<1 inch square), we added two to each tile to increase the robustness of detection. We used a plywood plank as our first version of the tile, but found it to be a bit too heavy. We then used these canvas boards that were significantly lighter. We hot-glued 1/4-in nuts to each of the FSRs and placed them near the center along one diagonal of the board. We then hot-glued washers and nuts to each of the four corners. As a result of this setup, the resistors typically had no force applied to them, because they hardly rested on the floor. However, once depressed, the board bended slightly and the FSRs were squeezed. We wired the two resistors in parallel, then in series with a 10KΩ resistor. Running 3.3 V across the setup and measuring the voltage at the intersection point gave us voltage levels of basically 0V/3.2V when unpressed/pressed, which meant we could just wire up each tile to a digital pin. We constructed four of these, wired them up to a protoboard hidden underneath the center tile, then fed a ribbon cable up to our main protoboard.

![alt text](resources/tile1.JPG "First Tile")

*Our First Tile*

---

### Results

#### General Usability

####Beat Detection

The beat detection algorithm was remarkably successful. We tested using a variety of different music and different genres. Once the algorithm was implemented on the PIC and arrows were being sent to the monitor, we had a simple trial and error system of testing. In order to calibrate timing, we would play one drum beat, then measure the difference in time between when it played on the speakers and when the generated arrow reached the top of the screen. We adjusted the buffer size on the PIC and the speed of the arrows on the Mac to achieve synchronous behavior. Once this was done, we simply tried to play as much music as we could. Early attempts at this revealed that preset thresholds simply were not effective at doing beat detection between many different types of music. We then implemented an active averaging system to detect beats (see *Software Design: Signal Processing and Beat Detection*), which proved to be significantly more versatile.

Our algorithm is extremely effective at detecting beats and generating interesting arrow patterns when the music playing has distinctive low frequency components that manifest themselves in short beats. Playing classic rock and other music with loud, repetitive drums (AC/DC's Highway to Hell; Darius Rucker's Wagon Wheel) results in clear beat detection as soon as the drums kick in. Other sounds (guitar modulation, vocals, etc), result in variations in the arrow sequences. Our system also performs very well with electronic music (Mr. FInger's Mystery of Love; LCD Soundsystem's Dance Yourself Clean). These songs also have distinctive drums or quick base notes that make up the beat of the song. Since the base notes here are electronic, and can actually have a melody (as opposed to analog drums which are fairly constant in tone from hit to hit), they can result in really interesting, fun to play patterns.

**INSERT VIDEOs HERE**

As we expected at the onset of the project, certain genres of music did not work well for our system. We had two different types of failure cases. In the first case, no beats would be detected. This occurs when a piece of music is slower and has few cases of 'spikes in the signal,' so to speak. The Discrete Wavelet Transform essentially detects high energy transitions that look like the mother wavelet (see *High Level Design: Beat Detection*), and these are much less common in songs without modern bass. Classical music obviously fails to have beats detected. We also had poor results with jazz (Louis Armstrong, Dave Brubeck's Take Five). 

The other failure case we encountered was when too many beats were detected. This occurred primarily when base notes were too long, or the music simply had 'too much going on.' We consistently failed to generate anything remotely usable when playing hip-hop music, because long 808 bass notes caused our beat detection system to freak out, generating far too many notes. Quick hi-hats also resulted in many beat detections. This oversaturation made the game unplayable.

**Insert other video here**

####Safety



---

###Conclusions

Taken holistically, we were extremely pleased with the outcome of our project. The beat detection and arrow generation on certain songs was extremely good, and resulted in very playable patterns (see Results section). The application ran extremely well on the Mac, and user input using the pad was very straightforward. We attracted quite a lot of attention in the lab while demoing, which was extremely satisfying. Two areas for improvement stood out to us as we completed the project: A) Expanding our beat detection for more areas of music, and B) improving the floor tile system. 

Our beat detection was a fairly robust system, which was able to distinguish beats from music with simple beat structures and heavy drums (genres like classic rock and techno). As noted above, genres with heavy, longer basslines (for example, hip-hop with long, droning 808 bass), resulted in over detection and too many arrows appearing on screen. We talked about modifying either the PIC code or the Mac code to identify these longer basslines and display them on the screen as either one single beat, or an opportunity for the user to hold down one arrow pad. We ultimately decided not to do this because of the scale of the changes we would need to make. Future improvements to the system should certainly include this.

Perhaps the most obvious improvement necessary is to the floor tiles. While they technically did work - when someone placed their weight on a tile, the system would almost immediately (within 60 milliseconds) recognize a press. However, the tiles were simply too fragile (or seemed too fragile) to be used for the actual game. Each one was made out of a canvas board, propped up on the corners by metal nuts and washers. As a result, they felt very unsteady and breakable when a user put their weight on them. The center tile, where the user put their weight for the majority of playing time, was especially problematic because we chose to put the wiring protoboard underneath it. It felt like a jump on that page would result in the board snapping. It was thus difficult for anyone to actually play on the system. Moreover, the glue was indeed quite delicate, and we often had nuts and sensors fall off. We simply did not have time to revise our board design. If we were to improve the system, we could go in one of two directions. Either stiffen the boards by making them out of a sturdier material like wood (as our first, proof of concept board was), or get rid of the boards altogether, and make a mat-based system. We could still incorporate our force sensitive resistors (which worked extremely well), by putting some sort of light tile into the mat, so that the force of a step would be distributed onto the FSRs. Overall though, we were extremely happy with how our project turned out.

Our project is heavily inspired by the game Dance Dance Revolution, which is indeed a trademarked property. However, the name 'Dance Dance Evolution' has [no active trademarks associated with it](http://tmsearch.uspto.gov/bin/showfield?f=toc&state=4805%3Aq2zjoa.1.1&p_search=searchss&p_L=50&BackReference=&p_plural=yes&p_s_PARA1=&p_tagrepl~%3A=PARA1%24LD&expr=PARA1+AND+PARA2&p_s_PARA2=dance+dance+evolution&p_tagrepl~%3A=PARA2%24COMB&p_op_ALL=AND&a_default=search&a_search=Submit+Query&a_search=Submit+Query). In a sense, we did reverse engineer the mechanics of their game, but we could not find a specific patent for the game play mechanism. We do not think our beat detection algorithm/approach is novel enough to patent (see the Tzanetakis paper in our references). We reuse some code written by Bruce Land and Syed Tahmid Mahbub for the course. We also relied heavily on the GNU Scientific Library and Matt Gallagher's Core Animation library. Since our project is entirely open source and we are not seeking to mass-produce this for profit, we have no reason to believe we are violating any intellectual property.

We believe that our project is fully compliant with IEEE standards. We embarked on the project in an effort to bring an enjoyable, fun game to the masses, and that is ultimately what we ended up doing. Our project's individual components are all harmless: Floor switches, audio buffering, and beat detection. The IEEE code puts emphasis on protecting the public's health and safety. As a result we made special effort to make sure individuals do not trip or injure their feet when playing the game by putting the tiles low to the ground and making sure they would not slide around. As noted above, we do not think we are making any IP violations through the project. Even if our interpretation of the law is incorrect, we doubt that the publication of a single open source version of the Dance Dance Revolution game will cause the game publishers to lose any income. By making our code, schematics, and methodology publically available, we hope to encourage understanding of technology and spark interest in embedded design and signal processing, as per point five of the IEEE Code of Ethics. Moreover, we have noted all contributors and sources of code and ideas. In summation: Our project is fairly benign, and we hope it brings joy to all who play it.

We found no legal issues with our project. The only concern was that of intellectual property violations, and as noted above, we do not violate any trademarks. 

---

### Acknowledgements

We would like to heartily thank Interlink Electronics for their generous donation of 10 force sensitive resistors (part number FSR402). Their contribution made our project possible.

In addition, we are extremely grateful to Professor Bruce Land, who provided an immeasurable amount of help. Huge thanks also to Professor David Delchamps, whose lectures and advice inspired the signal analysis component of our project. Mark Zhao was a spectacular, well-informed TA.

---

### Appendix A: Permissions

The group approves this report for inclusion on the course website.

The group approves the video for inclusion on the course Youtube channel.

---

### Appendix B: Commented Code

should put links to other pages/github here

---

###Appendix C: Schematics

TODO EVERYTHING

---

### Appendix D: Budgeting

| Part                               | Quantity | Cost   |
| ---------------------------------- | :------- | ------ |
| Force Sensitive Resistors (FSR402) | 10       | $0.00  |
| Auxillary Audio Cord               | 1        | $1.74  |
| 10"x10" Canvas Boards              | 5        | $10.00 |
| PIC32 Large Development Board      | 1        | $10.00 |
| Serial to Serial Cable             | 1        | $5.00  |
| Jumper Cables                      | ???      |        |
| 6" Solder Board                    | 2        | $5.00  |
| 9V Power Supply                    | 2        | $10.00 |
| Lab Speakers                       | 1        | $2.00  |
| Header Sockets                     | ???      |        |
| PIC32MX250F128B                    | 2        | $10.00 |
| 23LC1024 SRAM                      | 1        | $2.32  |
| PIC32 Small Development Board      | 1        | $5.00  |
| **TOTAL**                          |          | $      |

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
* C implementation of beat detection

---

###Appendix F: References and Helpful Resources

[George Tzanetakis' wonderful paper on beat extraction with the discrete wavelet transform](http://soundlab.cs.princeton.edu/publications/2001_amta_aadwt.pdf)

[Rafat Hussain's C Wave Library, which we didn't end up using, but may be a helpful resource](https://github.com/rafat/wavelib)

[The GNU Scientific Library](https://github.com/ampl/gsl)

[Datasheet for Interlink FSR402](http://interlinkelectronics.com/datasheets/Datasheet_FSR.pdf)

[Prolific Serial Driver](http://www.prolific.com.tw/US/ShowProduct.aspx?p_id=229&pcid=41)

[Matt Gallagher's Core Animation library](https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/CoreAnimation_guide/Introduction/Introduction.html)

[Spotify playlist of songs that work well with our system](https://open.spotify.com/user/ikneadthis/playlist/3bhtbVHmOR9QFXgW1xDQiN)

[PIC32 Peripheral Library](http://ww1.microchip.com/downloads/en/DeviceDoc/32bitPeripheralLibraryGuide.pdf)

[IEEE Code of Ethics](https://www.ieee.org/about/corporate/governance/p7-8.html)

**THINGS TO ADD: LINK TO OUR GITHUB/link to serial library/link to matt gallaghers animation library**