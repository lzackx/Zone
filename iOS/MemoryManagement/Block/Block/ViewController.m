//
//  ViewController.m
//  Block
//
//  Created by lzackx on 2018/3/06.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self testBlock];
    
}

- (void)testBlock {
    int i = 0;
    
    void (^block0)(void) = ^{
        NSLog(@"i is: %i", i);
    };
    
    i = 1;
    
    // 调用后控制台的结果是0
    block0();
    
    /*
     __block这里起到共享存储的作用。
     当使用__block声明变量时，意味着变量是存在于在作用域范围之内声明的块共享的存储空间。
     所以当块中取以__block声明的变量时，获取的位置跟作用范围内的一致。
     同样的情况但不以__block声明时，因为不共享，自然block中就是定义时捕获的值了。
     */
    __block int j = 0;
    void (^block1)(void) = ^{
        NSLog(@"j is: %i", i);
    };
    
    j = 1;
    
    // 调用后控制台的结果是1
    block1();
}

@end
