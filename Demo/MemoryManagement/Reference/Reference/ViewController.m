//
//  ViewController.m
//  Reference
//
//  Created by lzackx on 2018/3/06.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property NSString *blockProperty;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.blockProperty = @"Block Property";
    
    // 情况1 会出现循环引用，导致内存泄漏
//    void (^block)(void) = ^{
//        NSLog(@"%@", self.blockProperty);
//    };
    
    // 情况2 不会出现循环引用，因为block中并没有让self的引用计数加一
//    __weak ViewController *weakSelf = self;
//    void (^block)(void) = ^{
//        NSLog(@"%@", weakSelf.blockProperty);
//    };
    
    // 情况3 不会出现循环引用，并且能保证block中代码运行时，确保实例变量不为nil
    __weak ViewController *weakSelf = self;
    void (^block)(void) = ^{
        __strong ViewController *strongSelf = weakSelf;
        NSLog(@"%@", strongSelf.blockProperty);
    };
    
    block();
}



@end
