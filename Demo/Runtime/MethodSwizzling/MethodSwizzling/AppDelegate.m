//
//  AppDelegate.m
//  MethodSwizzling
//
//  Created by lzackx on 2018/3/15.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "AppDelegate.h"
#import <objc/runtime.h>
#import "SwizzlingMethodObject.h"
#import "ViewController.h"
#import "UIViewController+MethodSwizzling.h"

@interface AppDelegate ()

@property SwizzlingMethodObject *smObject;

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    [self initMethodSwizzling];
    return YES;
}

- (void)initMethodSwizzling {
    
    // 原方法
    Method original_viewDidLoad = class_getInstanceMethod([UIViewController class], @selector(viewDidLoad));
    IMP original_viewDidLoad_imp = method_getImplementation(original_viewDidLoad);
    
    // 目标方法
    Method method_swizzling_viewDidLoad = class_getInstanceMethod([UIViewController class], @selector(ms_viewDidLoad));
    IMP ms_viewDidLoad_imp = method_getImplementation(method_swizzling_viewDidLoad);
    
    self.smObject = [[SwizzlingMethodObject alloc] initWithOriginalClass:[UIViewController class]
                                                        OriginalSelector:@selector(viewDidLoad)
                                                             OriginalIMP:original_viewDidLoad_imp
                                                                 SMClass:[UIViewController class]
                                                              SMSelector:@selector(ms_viewDidLoad)
                                                                   SMIMP:ms_viewDidLoad_imp];
    
    [self.smObject swizzle];
}


@end
