//
//  ViewController.m
//  CategoryAndExtension
//
//  Created by lzackx on 2018/3/06.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"
#import "ViewControllerPrivate.h"
#import "UIViewController+Category.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // 调用extension中添加的私有属性
    self.extensionVariable = @"Extension";
    NSLog(@"%@", self.extensionVariable);
    
    // 调用category中添加的静态方法
    [UIViewController method];
}

@end
