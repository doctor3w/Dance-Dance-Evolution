//
//  GameObjectLayer.m
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

#import "GameObjectLayer.h"
#import "GameData.h"
#import "GameObject.h"

@implementation GameObjectLayer

//
// initWithGameObjectKey
//
// Init method for the object.
//
- (id)initWithGameObjectKey:(NSString *)newGameObjectKey
{
	self = [super init];
	if (self != nil)
	{
		gameObjectKey = newGameObjectKey;
		
		[[[GameData sharedGameData] gameObjects]
			addObserver:self
			forKeyPath:gameObjectKey
			options:NSKeyValueObservingOptionNew
			context:nil];

		[self update];
	}
	return self;
}

//
// actionForKey:forKey:
//
// Override all default actions with a linear timing function
//
- (id<CAAction>)actionForKey:(NSString *)aKey
{
	return nil;
}

//
// update
//
// Updates the layer based on the elements in the dictionary
//
- (void)update
{
	GameObject *gameObject = [[[GameData sharedGameData] gameObjects] objectForKey:gameObjectKey];
	double gameHeight = [[GameData sharedGameData] gameHeight];

	NSString *gameObjectImageName = gameObject.imageName;
	double x = gameObject.x * gameHeight;
	double y = gameObject.y * gameHeight;
	double width = gameObject.width * gameHeight;
	double height = gameObject.height * gameHeight;
	double angle = gameObject.angle;
	BOOL visible = gameObject.visible;

	self.imageName = gameObjectImageName;
	self.bounds = CGRectMake(0, 0, width, height);
	self.position = CGPointMake(x, y);
	self.transform = CATransform3DMakeRotation(angle, 0, 0, 1.0);
	self.hidden = !visible;
    self.opacity = gameObject.opacity;
}

//
// observeValueForKeyPath:ofObject:change:context:
//
// Receives key value change notifications for the following keys.
//
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object
	change:(NSDictionary *)change context:(void *)context
{
	if ([keyPath isEqualTo:gameObjectKey])
	{
		NSMutableDictionary *value = [change objectForKey:NSKeyValueChangeNewKey];
		if ([value isEqual:[NSNull null]])
		{
			[self removeFromSuperlayer];
			
			return;
		}
		
		[self update];
		return;
	}
	
	[super observeValueForKeyPath:keyPath ofObject:object change:change
		context:context];
}

//
// dealloc
//
// Releases instance memory.
//
//- (void)dealloc
//{
//    if (gameObjectKey)
//    {
//        [[[GameData sharedGameData] gameObjects] removeObserver:self forKeyPath:gameObjectKey];
//    }
//    [gameObjectKey release];
//    [super dealloc];
//}

@end
