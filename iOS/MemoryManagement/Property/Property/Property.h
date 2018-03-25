//
//  Property.h
//  Property
//
//  Created by lzackx on 2018/3/06.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Property : NSObject

/* 默认的property属性为readwrite、assign、atomic，
 其中assign适用于基础数据类型和C数据类型，意为简单赋值
 */
@property (atomic, readwrite, assign) int i;

@property NSString *string;

/*
 与assign不同的是，strong适用于继承NSObject的对象，引用计数会增1，即对实例对象保留所有权。
 若被定为assign的话，当实例对象引用计数为0时，属性就会变成悬垂指针，指向的数据未知。
 */
@property (atomic, readwrite, strong) NSNumber *number;

/*
 weak与strong和assign都不一样，weak不增加引用计数，也不持有对象，
 在实例对象的引用计数为0时，指针会被自动设置为nil。
 */
@property (atomic, readwrite, weak) NSNumber *weakNumber;


// 对于BOOL属性，默认的getter就是添加is前缀
@property (readonly, getter=isRb) BOOL rb;

- (instancetype)init

@end
