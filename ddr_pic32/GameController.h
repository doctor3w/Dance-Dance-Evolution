//
//  GameController.h
//  ddr_pic32
//
//  Adapted by Drew Dunne on 11/14/17.
//
//  Created by Matt Gallagher on 15/02/09.
//  Copyright 2009 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file without charge in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//

#import <ORSSerial/ORSSerial.h>

@interface GameController : NSObject <ORSSerialPortDelegate, NSUserNotificationCenterDelegate>
{
	CALayer *backgroundLayer;
	IBOutlet NSView *contentView;
	IBOutlet NSView *buttonContainerView;
}

@property (nonatomic, strong) ORSSerialPortManager *serialPortManager;
@property (nonatomic, strong) ORSSerialPort *serialPort;
@property (nonatomic, strong) NSArray *availableBaudRates;

- (IBAction)newGame:(id)sender;
- (IBAction)toggleFullscreen:(id)sender;

@end
