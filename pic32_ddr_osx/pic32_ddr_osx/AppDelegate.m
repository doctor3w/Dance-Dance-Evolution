//
//  AppDelegate.m
//  pic32_ddr_osx
//
//  Created by Drew Dunne on 10/24/17.
//  Copyright © 2017 Drew Dunne. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    DDRViewController *rootVC = [[DDRViewController alloc] initWithNibName:nil bundle:nil];
    [self.window.contentView addSubview:rootVC.view];
    rootVC.view.frame = ((NSView*)self.window.contentView).bounds;
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


@end
