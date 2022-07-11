//
//  TestObject.m
//  Ivar&Property
//
//  Created by lzackx on 2018/3/15.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "TestObject.h"

@interface TestObject ()

@property NSString *privateString;

@end

@implementation TestObject

- (instancetype)init
{
    self = [super init];
    if (self) {
        _publicString = @"public";
        _privateString = @"private";
    }
    return self;
}

@end
