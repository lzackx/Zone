//
//  ViewController.m
//  Source0_NonPortBased
//
//  Created by lzackx on 2018/3/20.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property CFRunLoopSourceRef source0;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    [self runSource0];
    
}

void RunLoopSourceScheduleRoutine (void *info, CFRunLoopRef rl, CFStringRef mode) {
    NSLog(@"Schedule routine: source is added to runloop");
}

void RunLoopSourceCancelRoutine (void *info, CFRunLoopRef rl, CFStringRef mode) {
    NSLog(@"Cancel Routine: source removed from runloop");
}

void RunLoopSourcePerformRoutine (void *info) {
    NSLog(@"Perform Routine: source has fired");
}

- (CFRunLoopSourceRef)createSource0 {
    
    /*
     typedef struct {
     CFIndex    version;
     void *    info;
     const void *(*retain)(const void *info);
     void    (*release)(const void *info);
     CFStringRef    (*copyDescription)(const void *info);
     Boolean    (*equal)(const void *info1, const void *info2);
     CFHashCode    (*hash)(const void *info);
     void    (*schedule)(void *info, CFRunLoopRef rl, CFRunLoopMode mode);
     void    (*cancel)(void *info, CFRunLoopRef rl, CFRunLoopMode mode);
     void    (*perform)(void *info);
     } CFRunLoopSourceContext;
     */
    CFRunLoopSourceContext context = {
        0,
        (__bridge void *)(self),
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        RunLoopSourceScheduleRoutine,
        RunLoopSourceCancelRoutine,
        RunLoopSourcePerformRoutine
    };
    CFRunLoopSourceRef source0 = CFRunLoopSourceCreate(NULL, 0, &context);
    return source0;
}

- (void)addToCurrentRunLoopWithSource0:(CFRunLoopSourceRef)source0 {
    
    CFRunLoopRef runLoop = CFRunLoopGetCurrent();
    CFRunLoopAddSource(runLoop, source0, kCFRunLoopDefaultMode);
}

- (void)fireSource0:(CFRunLoopSourceRef)source0 {
    
    CFRunLoopSourceSignal(source0);
    CFRunLoopRef runLoop = CFRunLoopGetCurrent();
    CFRunLoopWakeUp(runLoop);
}

- (void)runSource0 {
    
    self.source0 = [self createSource0];
    [self addToCurrentRunLoopWithSource0:self.source0];
    [self fireSource0:self.source0];

}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    
    CFRunLoopRemoveSource(CFRunLoopGetCurrent(), self.source0, kCFRunLoopDefaultMode);
}

@end










