//
//  ImageLayer.h
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

#import <Cocoa/Cocoa.h>

@interface ImageLayer : CALayer
{
	NSString *imageName;
}

@property (nonatomic, retain) NSString *imageName;

- (id)initWithImageNamed:(NSString *)newImageName
	frame:(NSRect)newFrame;

@end

