//
//  ViewController.m
//  RunLoop
//
//  Created by lzackx on 2018/4/8.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.

    // Timer
    [self testRunLoopTimer];
    [self testAsyncRunLoopTimer];
}

// MARK: Timer
- (void)testAsyncRunLoopTimer {
    
    __weak id weakSelf = self;
    dispatch_queue_t queue = dispatch_queue_create("async_queue", DISPATCH_QUEUE_CONCURRENT);
    dispatch_async(queue, ^{
        [weakSelf testRunLoopTimer];
        [NSRunLoop.currentRunLoop run];
    });
}

- (void)testRunLoopTimer {
    
    [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(timerFireMethod:) userInfo:@"scheduled" repeats:YES];
    
    NSTimer *timer = [NSTimer timerWithTimeInterval:1.0 target:self selector:@selector(timerFireMethod:) userInfo:@"object" repeats:YES];
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
    
}

- (void)timerFireMethod:(NSTimer *)timer {
    NSLog(@"I am from testMainRunLoopTimerInDefaultMode: %s, mode: %@", __func__, [[NSRunLoop currentRunLoop] currentMode]);
}


@end
