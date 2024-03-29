//
//  ViewController.m
//  Observer
//
//  Created by lzackx on 2018/3/20.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    [self runRunLoopObserver];
}

- (void)createRunLoopObserver {
    
    // The application uses garbage collection, so no autorelease pool is needed.
    // Create a run loop observer and attach it to the run loop.
    /*
     typedef struct {
         CFIndex    version;
         void *    info;
         const void *(*retain)(const void *info);
         void    (*release)(const void *info);
         CFStringRef    (*copyDescription)(const void *info);
     } CFRunLoopObserverContext;
     */
    CFRunLoopObserverContext context = {0, (__bridge void *)(self), NULL, NULL, NULL};
    CFRunLoopObserverRef observer = CFRunLoopObserverCreate(kCFAllocatorDefault,
                                                            kCFRunLoopAllActivities,
                                                            YES,
                                                            0,
                                                            &observerCallBack,
                                                            &context);
    if (observer) {
        CFRunLoopRef cfLoop = CFRunLoopGetCurrent();
        CFRunLoopAddObserver(cfLoop, observer, kCFRunLoopDefaultMode);
        CFRelease(observer);
    }
}

void observerCallBack(CFRunLoopObserverRef observer, CFRunLoopActivity activity, void *info) {
    
    /*
     typedef CF_OPTIONS(CFOptionFlags, CFRunLoopActivity) {
         kCFRunLoopEntry = (1UL << 0),              // 1
         kCFRunLoopBeforeTimers = (1UL << 1),       // 2
         kCFRunLoopBeforeSources = (1UL << 2),      // 4
         kCFRunLoopBeforeWaiting = (1UL << 5),      // 32
         kCFRunLoopAfterWaiting = (1UL << 6),       // 64
         kCFRunLoopExit = (1UL << 7),               // 128
         kCFRunLoopAllActivities = 0x0FFFFFFFU
     };
     */
    NSLog(@"%s: observer = %@, activity = %lu, info = %@", __func__, observer, activity, info);
    /* results
     observerCallBack: observer = <CFRunLoopObserver 0x60400013bc60 [0x10f35cc80]>{valid = Yes, activities = 0xfffffff, repeats = Yes, order = 0, callout = observerCallBack (0x10de284a0), context = <CFRunLoopObserver context 0x7fd1de711910>}, activity = 2, info = <ViewController: 0x7fd1de711910>
     observerCallBack: observer = <CFRunLoopObserver 0x60400013bc60 [0x10f35cc80]>{valid = Yes, activities = 0xfffffff, repeats = Yes, order = 0, callout = observerCallBack (0x10de284a0), context = <CFRunLoopObserver context 0x7fd1de711910>}, activity = 4, info = <ViewController: 0x7fd1de711910>
     observerCallBack: observer = <CFRunLoopObserver 0x60400013bc60 [0x10f35cc80]>{valid = Yes, activities = 0xfffffff, repeats = Yes, order = 0, callout = observerCallBack (0x10de284a0), context = <CFRunLoopObserver context 0x7fd1de711910>}, activity = 32, info = <ViewController: 0x7fd1de711910>
     observerCallBack: observer = <CFRunLoopObserver 0x60400013bc60 [0x10f35cc80]>{valid = Yes, activities = 0xfffffff, repeats = Yes, order = 0, callout = observerCallBack (0x10de284a0), context = <CFRunLoopObserver context 0x7fd1de711910>}, activity = 64, info = <ViewController: 0x7fd1de711910>
     Fired
     */
}

- (void)timerFired:(NSTimer *)timer {
    NSLog(@"Fired");
}

- (void)runRunLoopObserver {
    
    [self createRunLoopObserver];
    // Create and schedule the timer.
    [NSTimer scheduledTimerWithTimeInterval:0.1 target:self
                                   selector:@selector(timerFired:)
                                   userInfo:nil
                                    repeats:YES];
}


@end










