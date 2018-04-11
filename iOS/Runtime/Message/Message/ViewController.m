//
//  ViewController.m
//  Message
//
//  Created by lzackx on 2018/3/15.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"
#import <objc/message.h>
#import "MessagingObject.h"

@interface ViewController ()

@property MessagingObject *messagingObject;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.messagingObject = [[MessagingObject alloc] init];
    [self messagingTest];
    [self dynamicMethodTest];
    [self messageForwardingTest];
    
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundeclared-selector"
/*
 因为MessagingObject.h中，没有dynamicMethodIMP和surrogateMethod的声明，所以会warnings。看着烦，可以这么去掉。
 */
- (void)messagingTest {
    
    void (*directMethod)(id, SEL, NSString *) = (void (*)(id, SEL, NSString *))[self.messagingObject methodForSelector:@selector(methodWithParameter:)];
    directMethod(self.messagingObject, @selector(methodWithParameter:), @"directly invoke");
    // Parameter: directly invoke
    
}

- (void)dynamicMethodTest {
    
    objc_msgSend(self.messagingObject, @selector(dynamicMethodIMP));
    // dynamicMethodIMP called
}

- (void)messageForwardingTest {
    
    [self.messagingObject performSelector:@selector(surrogateMethod)];
    // surrogateMethod called
}
#pragma clang diagnostic pop

@end










