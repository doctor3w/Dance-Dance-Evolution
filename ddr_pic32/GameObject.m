//
//  GameObject.m
//  Quartzeroids2
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

#import "GameObject.h"
#import "GameData.h"

const double GAME_OBJECT_BOUNDARY_EXCESS = 0.1;

@implementation GameObject

@synthesize keyInGameData;
@synthesize angle;
@synthesize x;
@synthesize y;
@synthesize width;
@synthesize height;
@synthesize speed;
@synthesize trajectory;
@synthesize lastUpdateInterval;
@synthesize visible;
@synthesize imageName;
@synthesize opacity;

//
// initWithImageName:xFraction:yFraction:widthFraction:heightFraction:visible:
//
// Creates a new game object. The object is added to the gameObjects dictionary
// using the "name" as a key but is also returned for convenience.
//
- (id)initWithImageName:(NSString *)newImageName
	x:(double)newX
	y:(double)newY
	width:(double)newWidth
	height:(double)newHeight
	visible:(BOOL)newVisible
{
	self = [super init];
	if (self)
	{
		self.imageName = newImageName;
		angle = 0;
		x = newX;
		y = newY;
		width = newWidth;
		height = newHeight;
		visible = newVisible;
		speed = 0;
		trajectory = 0;
		lastUpdateInterval = 0;
        opacity = 1;
	}

	return self;
}

//
// updateWithTimeInterval:
//
// Updates the object's properties given the elapsed time.
// This method should not interact with existing GameObjects (that should be
// done in -(void)collide).
//
// Returns YES if object data should be removed. NO otherwise.
//
- (BOOL)updateWithTimeInterval:(NSTimeInterval)timeInterval
{
	x += timeInterval * speed * cos(trajectory);
	y += timeInterval * speed * sin(trajectory);
	
	if (x > GAME_ASPECT + (0.5 + GAME_OBJECT_BOUNDARY_EXCESS) * width)
	{
		x = -0.5 * width;
	}
	else if (x < -(0.5 + GAME_OBJECT_BOUNDARY_EXCESS) * width)
	{
		x = GAME_ASPECT + 0.5 * width;
	}
	
	if (y > 1.0 + (0.5 + GAME_OBJECT_BOUNDARY_EXCESS) * height)
	{
		y = -0.5 * height;
	}
	else if (y < -(0.5 + GAME_OBJECT_BOUNDARY_EXCESS) * height)
	{
		y = 1.0 + 0.5 * height;
	}
	
	lastUpdateInterval = timeInterval;
	return NO;
}

//
// dealloc
//
// Releases instance memory.
//
//- (void)dealloc
//{
//    [imageName release];
//    [super dealloc];
//}

@end



