//
//  GameController.m
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

#import "GameController.h"
#import "GameData.h"
#import "ImageLayer.h"
#import "GameObjectLayer.h"

@implementation GameController

- (instancetype)init
{
    self = [super init];
    if (self)
    {
        self.serialPortManager = [ORSSerialPortManager sharedSerialPortManager];
        self.availableBaudRates = @[@300, @1200, @2400, @4800, @9600, @14400, @19200, @28800, @38400, @57600, @115200, @230400];
        
        NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
        [nc addObserver:self selector:@selector(serialPortsWereConnected:) name:ORSSerialPortsWereConnectedNotification object:nil];
        [nc addObserver:self selector:@selector(serialPortsWereDisconnected:) name:ORSSerialPortsWereDisconnectedNotification object:nil];
        
    }
    return self;
}

//
// updateContentViewFrame:
//
// When the window (and hence the window's content view) changes size, this
// will resize, reposition and rescale the content by adjusting the
// backgroundLayer (to which all other CALayers are parented).
//
- (void)updateContentViewFrame:(NSNotification *)notification
{
	double gameWidth = [[GameData sharedGameData] gameWidth];
	double gameHeight = [[GameData sharedGameData] gameHeight];
	
	NSSize contentSize = [contentView bounds].size;

	NSSize aspectSize = contentSize;
	double scale;
	if ((aspectSize.width / aspectSize.height) > (gameWidth / gameHeight))
	{
		scale = aspectSize.height / gameHeight;
		aspectSize.width = aspectSize.height * (gameWidth / gameHeight);
	}
	else
	{
		scale = aspectSize.width / gameWidth;
		aspectSize.height = aspectSize.width * (gameHeight / gameWidth);
	}
	
	[CATransaction begin];
	[CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];
	backgroundLayer.transform = CATransform3DMakeScale(scale, scale, 1.0);
	backgroundLayer.frame =
		CGRectMake(
			0.5 * (contentSize.width - aspectSize.width),
			0.5 * (contentSize.height - aspectSize.height),
			aspectSize.width,
			aspectSize.height);
	[CATransaction commit];

	[contentView becomeFirstResponder];
}

//
// createImageLayerForGameObject:
//
// The game data sends a notification when a new game object is created. We
// create a layer to display that object here. The layer will maintain
// its own observations of further changes.
//
- (void)createImageLayerForGameObject:(NSNotification *)notification
{
	NSString *gameObjectKey = [notification object];
	
	GameObjectLayer *newLayer =
		[[GameObjectLayer alloc]
			initWithGameObjectKey:gameObjectKey];

	[CATransaction begin];
	[CATransaction
		setValue:[NSNumber numberWithBool:YES]
		forKey:kCATransactionDisableActions];
	[backgroundLayer addSublayer:newLayer];
	[CATransaction commit];
	
//    if ([gameObjectKey rangeOfString:GAME_ASTEROID_KEY_BASE].location == 0)
//    {
//        AsteroidFrontLayer *asteroidFrontLayer =
//            [[[AsteroidFrontLayer alloc]
//                initWithGameObjectKey:gameObjectKey]
//            autorelease];
//
//        [CATransaction begin];
//        [CATransaction
//            setValue:[NSNumber numberWithBool:YES]
//            forKey:kCATransactionDisableActions];
//        [backgroundLayer addSublayer:asteroidFrontLayer];
//        [CATransaction commit];
//    }
}

//
// observeValueForKeyPath:ofObject:change:context:
//
// Receives key value change notifications for the following keys.
//
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object
                        change:(NSDictionary *)change context:(void *)context
{
    if ([keyPath isEqualToString:GAME_DATA_MSG_KEY])
    {
        NSString *value = [change objectForKey:NSKeyValueChangeNewKey];
        
        if ([value isEqual:[NSNull null]])
        {
            [[msgText layer] setHidden:YES];
        }
        else
        {
            [[msgText layer] setHidden:NO];
            [msgText setStringValue:value];
        }
        return;
    }
    if ([keyPath isEqualToString:GAME_DATA_SCORE_KEY])
    {
        NSString *value = [change objectForKey:NSKeyValueChangeNewKey];
        
        if (![value isEqual:[NSNull null]])
        {
            [msgText setStringValue:[NSString stringWithFormat:@"Score: %@",value]];
        }
        return;
    }
    
    [super observeValueForKeyPath:keyPath ofObject:object change:change
                          context:context];
}

//
// awakeFromNib
//
// Creates the background layer and sets the startup state.
//
- (void)awakeFromNib
{
	[contentView layer].backgroundColor = CGColorCreateGenericRGB(0, 0, 0, 1);
	CGColorRelease([contentView layer].backgroundColor);
	
    [msgText setHidden:YES];
    
	backgroundLayer =
		[[ImageLayer alloc]
			initWithImageNamed:@"bg"
			frame:NSZeroRect];
	backgroundLayer.masksToBounds = YES;
	[[contentView layer] insertSublayer:backgroundLayer atIndex:0];
	[self updateContentViewFrame:nil];
    
    [[[GameData sharedGameData] gameData]
         addObserver:self
         forKeyPath:GAME_DATA_MSG_KEY
         options:NSKeyValueObservingOptionNew
         context:nil];
    
    [[[GameData sharedGameData] gameData]
         addObserver:self
         forKeyPath:GAME_DATA_SCORE_KEY
         options:NSKeyValueObservingOptionNew
         context:nil];
	
	[[NSNotificationCenter defaultCenter]
		addObserver:self
		selector:@selector(updateContentViewFrame:)
		name:NSViewFrameDidChangeNotification
		object:contentView];
	[[NSNotificationCenter defaultCenter]
		addObserver:self
		selector:@selector(createImageLayerForGameObject:)
		name:GAME_OBJECT_NEW_NOTIFICATION
		object:nil];
}

//
// newGame:
//
// Starts the game.
//
- (IBAction)newGame:(id)sender
{
    if (self.serialPort) {
        self.serialPort.parity = ORSSerialPortParityNone;
        self.serialPort.numberOfStopBits = 1;
        self.serialPort.baudRate = @9600;
        self.serialPort.delegate = self;
        if (!self.serialPort.isOpen)
            [self.serialPort open];
        [buttonContainerView setHidden:YES];
        [contentView becomeFirstResponder];
        
        [[GameData sharedGameData] newGame];
    }
}

//
// toggleFullscreen:
//
// Toggles the fullscreen window for the game.
//
- (IBAction)toggleFullscreen:(id)sender
{
	if ([contentView isInFullScreenMode])
	{
		[contentView exitFullScreenModeWithOptions:nil];
	}
	else
	{
		[contentView enterFullScreenMode:[[contentView window] screen] withOptions:nil];
		
		for (NSView *view in [NSArray arrayWithArray:[contentView subviews]])
		{
			[view removeFromSuperview];
			[contentView addSubview:view];
		}
	}
}


#pragma mark - Actions

- (IBAction)openOrClosePort:(id)sender
{
    self.serialPort.isOpen ? [self.serialPort close] : [self.serialPort open];
}

#pragma mark - ORSSerialPortDelegate Methods

- (void)serialPortWasOpened:(ORSSerialPort *)serialPort
{
    //self.openCloseButton.title = @"Close";
}

- (void)serialPortWasClosed:(ORSSerialPort *)serialPort
{
    //self.openCloseButton.title = @"Open";
}

- (void)serialPort:(ORSSerialPort *)serialPort didReceiveData:(NSData *)data
{
    if (data.length > 0) {
        unsigned char byte = ((char *)[data bytes])[0];
        if (byte != 0) {
            NSLog(@"byte: %d",byte);
            // Actual game data received. invert.
            unsigned char in_arrows = ((~byte) >> 4) & 0xf;
            NSLog(@"arrows: %d",in_arrows);
            unsigned char new_arrows = (~byte) & 0x0f;
            NSLog(@"new: %d",new_arrows);
            [[GameData sharedGameData] highlightOutlineArrows:in_arrows];
            if (new_arrows != 0)
                [[GameData sharedGameData] addArrowSeq:new_arrows];
        }
    }
}

- (void)serialPortWasRemovedFromSystem:(ORSSerialPort *)serialPort;
{
    // After a serial port is removed from the system, it is invalid and we must discard any references to it
    self.serialPort = nil;
    //    self.openCloseButton.title = @"Open";
}

- (void)serialPort:(ORSSerialPort *)serialPort didEncounterError:(NSError *)error
{
    NSLog(@"Serial port %@ encountered an error: %@", serialPort, error);
}

#pragma mark - Notifications

- (void)serialPortsWereConnected:(NSNotification *)notification
{
    NSArray *connectedPorts = [notification userInfo][ORSConnectedSerialPortsKey];
    NSLog(@"Ports were connected: %@", connectedPorts);
}

- (void)serialPortsWereDisconnected:(NSNotification *)notification
{
    NSArray *disconnectedPorts = [notification userInfo][ORSDisconnectedSerialPortsKey];
    NSLog(@"Ports were disconnected: %@", disconnectedPorts);
}


#pragma mark - Properties

- (void)setSerialPort:(ORSSerialPort *)port
{
    if (port != _serialPort)
    {
        [_serialPort close];
        _serialPort.delegate = nil;
        
        _serialPort = port;
        
        _serialPort.delegate = self;
    }
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
