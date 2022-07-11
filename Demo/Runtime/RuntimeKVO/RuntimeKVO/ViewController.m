//
//  ViewController.m
//  RuntimeKVO
//
//  Created by lzackx on 2018/3/15.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"
#import "NSObject+KVOImplementation.h"

@interface ViewController ()

@property int i;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.i = 0;
//    [self addObserver:self forKeyPath:@"i" options:NSKeyValueObservingOptionNew context:nil];
    [self rt_addObserver:self forKeyPath:@"i" options:NSKeyValueObservingOptionNew context:nil];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    NSLog(@"Object: %@", object);
    NSLog(@"keyPath: %@", keyPath);
    NSLog(@"change: %@", change);
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    
    NSLog(@"%i touched", self.i);
    self.i++;
    
}

- (void)dealloc
{
    [self removeObserver:self forKeyPath:@"i"];
}

@end
