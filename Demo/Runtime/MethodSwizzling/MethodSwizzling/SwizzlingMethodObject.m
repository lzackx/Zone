//
//  SwizzlingMethodObject.m
//  MethodSwizzling
//
//  Created by lzackx on 2018/3/15.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "SwizzlingMethodObject.h"
#import <objc/objc.h>
#import <objc/runtime.h>

@interface SwizzlingMethodObject ()

@property (nonatomic, assign) Class original_class;
@property (nonatomic, assign) SEL original_selector;
@property (nonatomic, assign) IMP original_imp;
@property (nonatomic, assign) Class sm_class;
@property (nonatomic, assign) SEL sm_selector;
@property (nonatomic, assign) IMP sm_imp;

@end

@implementation SwizzlingMethodObject

- (instancetype)initWithOriginalClass:(Class)original_class
                     OriginalSelector:(SEL)original_selector
                          OriginalIMP:(IMP)original_imp
                              SMClass:(Class)sm_class
                           SMSelector:(SEL)sm_selector
                                SMIMP:(IMP)sm_imp
{
    self = [super init];
    if (self) {
        _original_class = original_class;
        _original_selector = original_selector;
        _original_imp = original_imp;
        _sm_class = sm_class;
        _sm_selector = sm_selector;
        _sm_imp = sm_imp;
    }
    return self;
}

- (void)swizzle {
    
    Method originalMethod = class_getInstanceMethod(self.original_class, self.original_selector);
    /*
     Method smMethod = class_getInstanceMethod(self.sm_class, self.sm_selector);
     method_exchangeImplementations(originalMethod, smMethod);
     // method_exchangeImplementations这个函数就等于下边两个函数的结合，也就是两个方法互换IMP
     method_setImplementation(originalMethod, self.sm_imp);
     method_setImplementation(smMethod, self.original_imp);
     */
    method_setImplementation(originalMethod, self.sm_imp);
}

@end
