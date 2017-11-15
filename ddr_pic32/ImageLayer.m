//
//  ImageLayer.m
//  Quartzeroids2
//
//  Created by Matt Gallagher on 13/02/09.
//  Copyright 2009 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file without charge in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//

#import "ImageLayer.h"


@implementation ImageLayer

@synthesize imageName;

//
// initWithImageNamed
//
// Init method for the object.
//
- (id)initWithImageNamed:(NSString *)newImageName
	frame:(NSRect)newFrame
{
	self = [super init];
	if (self != nil)
	{
		self.anchorPoint = CGPointMake(0.5, 0.5);
		imageName = newImageName;
		[self setNeedsDisplay];
		[self setFrame:NSRectToCGRect(newFrame)];
	}
	return self;
}

//
// setImageName:
//
// Override of accessor to ensure layer is redraw when change occurs.
//
- (void)setImageName:(NSString *)newImageName
{
	if (newImageName != imageName)
	{
		imageName = newImageName;
		[self setNeedsDisplay];
	} 
}

//
// drawInContext
//
// Draws the selected image in the layer.
//
- (void)drawInContext:(CGContextRef)ctx
{
	NSGraphicsContext *oldContext = [NSGraphicsContext currentContext];
	NSGraphicsContext *context =
		[NSGraphicsContext graphicsContextWithGraphicsPort:ctx flipped:NO];
	[NSGraphicsContext setCurrentContext:context];
	
	NSImage *image = [NSImage imageNamed:imageName];
	[image
		drawInRect:NSRectFromCGRect([self bounds])
		fromRect:[image alignmentRect]
		operation:NSCompositeSourceOver
		fraction:1.0];
	
	[NSGraphicsContext setCurrentContext:oldContext];
}

@end

