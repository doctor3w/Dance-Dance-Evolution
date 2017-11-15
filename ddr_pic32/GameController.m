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
// awakeFromNib
//
// Creates the background layer and sets the startup state.
//
- (void)awakeFromNib
{
	[contentView layer].backgroundColor = CGColorCreateGenericRGB(0, 0, 0, 1);
	CGColorRelease([contentView layer].backgroundColor);
	
	backgroundLayer =
		[[ImageLayer alloc]
			initWithImageNamed:@"bg"
			frame:NSZeroRect];
	backgroundLayer.masksToBounds = YES;
	[[contentView layer] insertSublayer:backgroundLayer atIndex:0];
	[self updateContentViewFrame:nil];
	
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
	[buttonContainerView setHidden:YES];
	[contentView becomeFirstResponder];
	
	[[GameData sharedGameData] newGame];
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

@end
