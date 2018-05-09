//
//  ViewController.m
//  Timer
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
    
    // Main thread
    [self testRunLoopTimer];
    // Secondary thread
    [self testAsyncRunLoopTimer];
    
}
    
// MARK: Timer
- (void)testAsyncRunLoopTimer {
    
    __weak id weakSelf = self;
    dispatch_queue_t queue = dispatch_queue_create("async_queue", DISPATCH_QUEUE_CONCURRENT);
    dispatch_async(queue, ^{
        
        [weakSelf testRunLoopTimer];
        /*
         这一行代码就很灵性，默认情况下，RunLoop对象在子线程中是没有创建对象的，调用currentRunLoop的时候会创建并返回，
         原文是：If a run loop does not yet exist for the thread, one is created and returned.
         说它灵性，还有一个原因就是假如没有source或者timer假如到RunLoop中作为运行对象，那么这个RunLoop会立即退出，
         在此处的代码中，如果把此行代码放到[weakSelf testRunLoopTimer]的前面，那么最终[weakSelf testRunLoopTimer]内的timer是不会运行的。
         原文：If no input sources or timers are attached to the run loop, this method exits immediately;
         otherwise, it runs the receiver in the NSDefaultRunLoopMode by repeatedly invoking runMode:beforeDate:.
         */
        [NSRunLoop.currentRunLoop run];
    });
}
    
- (void)testRunLoopTimer {
    
    [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(timerFireMethod:) userInfo:@"scheduled 1" repeats:YES];
    
    NSTimer *timer = [NSTimer timerWithTimeInterval:1.0 target:self selector:@selector(timerFireMethod:) userInfo:@"scheduled 2" repeats:YES];
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
    
}
    
- (void)timerFireMethod:(NSTimer *)timer {
    NSLog(@"I am from %s, mode: %@, userInfo: %@", __func__, [[NSRunLoop currentRunLoop] currentMode], timer.userInfo);
}
    
@end
