//
//  UIViewController+MethodSwizzling.m
//  MethodSwizzling
//
//  Created by lzackx on 2018/3/15.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "UIViewController+MethodSwizzling.h"
#import <objc/runtime.h>

@implementation UIViewController (MethodSwizzling)

- (void)ms_viewDidLoad {
    NSLog(@"Method Swizzling viewDidLoad");
}

@end
