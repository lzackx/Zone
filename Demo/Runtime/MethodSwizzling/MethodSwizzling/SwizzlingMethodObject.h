//
//  SwizzlingMethodObject.h
//  MethodSwizzling
//
//  Created by lzackx on 2018/3/15.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SwizzlingMethodObject : NSObject

- (instancetype)initWithOriginalClass:(Class)original_class
                     OriginalSelector:(SEL)original_selector
                          OriginalIMP:(IMP)original_imp
                              SMClass:(Class)sm_class
                           SMSelector:(SEL)sm_selector
                                SMIMP:(IMP)sm_imp;
- (void)swizzle;

@end
