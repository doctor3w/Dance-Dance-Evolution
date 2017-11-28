//
//  GameObject.h
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

#import <Cocoa/Cocoa.h>

@interface GameObject : NSObject
{
	NSString *keyInGameData;
    NSInteger secNum;
	NSString *imageName;
	double angle;
	double x;
	double y;
	double width;
	double height;
	double speed;
	double trajectory;
	double lastUpdateInterval;
    double opacity;
	BOOL visible;
}

@property (nonatomic, retain) NSString *keyInGameData;
@property (nonatomic) NSInteger secNum;
@property double angle;
@property double x;
@property double y;
@property double width;
@property double height;
@property double speed;
@property double trajectory;
@property double lastUpdateInterval;
@property double opacity;
@property BOOL visible;
@property (nonatomic, retain) NSString *imageName;

- (id)initWithImageName:(NSString *)newImageName
	x:(double)newX
	y:(double)newY
	width:(double)newWidth
	height:(double)newHeight
	visible:(BOOL)newVisible;
- (BOOL)updateWithTimeInterval:(NSTimeInterval)timeInterval;

@end



