//
//  ViewController.m
//  Ivar&Property
//
//  Created by lzackx on 2018/3/15.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"
#import <objc/runtime.h>
#import "TestObject.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self testIvar];
    [self testProperty];
}

- (void)testIvar {
    
    Ivar publicIvar = class_getInstanceVariable([TestObject class], "_publicString");
    NSLog(@"public Ivar name: %s, type encoding: %s, offset: %ti", ivar_getName(publicIvar), ivar_getTypeEncoding(publicIvar), ivar_getOffset(publicIvar));
    
    unsigned int outCount = 0;
    Ivar *ivarList = class_copyIvarList([TestObject class], &outCount);
    for (int i = 0; i < outCount; i++) {
        Ivar ivar = ivarList[i];
        const char *name = ivar_getName(ivar);
        const char *typeEncoding = ivar_getTypeEncoding(ivar);
        long offset = ivar_getOffset(ivar);    // 可以注意到，这里并非强转，用的是long，而非int，也就是说objc_ivar结构体并非如所看到的一样。
        NSLog(@"ivar name: %s, type encoding: %s, offset: %ti", name, typeEncoding, offset);
    }
    free(ivarList);
    /*
     public Ivar name: _publicString, type encoding: @"NSString", offset: 8
     ivar name: _publicString, type encoding: @"NSString", offset: 8
     ivar name: _privateString, type encoding: @"NSString", offset: 16
     */
}

- (void)testProperty {
    
    unsigned int outCount = 0;
    objc_property_t *propertyList = class_copyPropertyList([TestObject class], &outCount);
    for (int i = 0; i < outCount; i++) {
        objc_property_t property = propertyList[i];
        const char *propertyName = property_getName(property);
        const char *propertyAttribute = property_getAttributes(property);
        NSLog(@"property name: %s, attribute: %s", propertyName, propertyAttribute);
        unsigned int attributeOutCount = 0;
        objc_property_attribute_t *attributeList = property_copyAttributeList(property, &attributeOutCount);
        for (int j = 0; j < attributeOutCount; j++) {
            objc_property_attribute_t attribute = attributeList[j];
            NSLog(@"attribute name: %s, value: %s", attribute.name, attribute.value);
            
        }
        free(attributeList);
    }
    free(propertyList);
    /*
     property name: privateString, attribute: T@"NSString",&,V_privateString
     attribute name: T, value: @"NSString"
     attribute name: &, value:
     attribute name: V, value: _privateString
     property name: publicString, attribute: T@"NSString",&,V_publicString
     attribute name: T, value: @"NSString"
     attribute name: &, value:
     attribute name: V, value: _publicString
     */
}

@end










