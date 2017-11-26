//
//  GameData.h
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

#import <Cocoa/Cocoa.h>

typedef enum {
    kLeftArrow,
    kRightArrow,
    kUpArrow,
    kDownArrow
} kArrowType;

@class GameObject;

@interface GameData : NSObject
{
	NSMutableDictionary *gameObjects;
	SEL updateSelector;
	
	NSDate *lastUpdate;
	NSTimeInterval frameDuration;
	
	NSTimer *timer;
    
    NSInteger counter;
}

+ (GameData *)sharedGameData;
- (NSDictionary *)gameObjects;
- (double)gameWidth;
- (double)gameHeight;
- (void)newGame;
- (void)startUpdates;
- (void)stopUpdates;
- (void)addGameObject:(GameObject *)newGameObject forKey:(NSString *)gameObjectKey;
- (void)removeGameObjectForKey:(NSString *)gameObjectKey;
- (void)changeRunSelector:(SEL)newSelector;

- (void)addArrowSequence:(kArrowType[])arrows withSize:(size_t)n withSequenceKey:(NSString *)key;
- (void)highlightOutlineArrows:(char)highlights;

@end

extern NSString *GAME_OBJECT_NEW_NOTIFICATION;

extern const double GAME_ASPECT;
extern const double GAME_UPDATE_DURATION;

extern NSString *ARROW_KEY_BASE;



