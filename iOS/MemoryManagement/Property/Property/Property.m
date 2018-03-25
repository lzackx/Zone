//
//  Property.m
//  Property
//
//  Created by lzackx on 2018/3/06.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "Property.h"

@implementation Property


/*
 以string属性为例，以下是默认的属性会生成的部分。
 1. 默认情况下，属性会生成一个带下划线的实例变量。
 2. 默认rewrite的属性，会生成getter和setter访问器方法，而点语法（.）其实就是调用getter和setter。
 3. 当显示地为属性实现了访问器方法时，编译器会认为需要自己控制属性，所以就不会自动生成实例变量，所以在这种情况下，如果需要一个实例变量的话，需要使用@synthesize再请求生成。
 */
@synthesize string = _string;
- (NSString *)string {
    return _string;
}
- (void)setString:(NSString *)string {
    _string = string;
}

- (instancetype)init {
    /*
     开发中通常会使用这种方式进行初始化，目的是为了避免因KVC机制导致的副作用。
     例如属性的Setter方法。
     */
    self = [super init];
    if (self) {
        _i = 0;
        _string = @"";
        _number = @"";
        _rb = NO;
    }
    return self;
}

@synthesize rb = _rb;
- (BOOL)isRb {
    return _rb;
}

@end
