//
//  ViewController.m
//  AssemblyLanguage
//
//  Created by lzackx on 2018/3/20.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"


@interface ViewController ()
@end

@implementation ViewController

int function(int a, int b, int c) {
    
    NSLog(@"%d,%d,%d", a, b, c);
    return a + b + c;
}

- (int)methodWithA:(int)a b:(int)b c:(int)c {
    
    NSLog(@"%d,%d,%d", a, b, c);
    return a + b + c;
}

- (int)methodWithX:(int)x y:(int)y z:(int)z {
    
    function(x, y, z);
    NSLog(@"%d,%d,%d", x, y, z);
    return x + y + z;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    int parameter1 = 1;
    int parameter2 = 2;
    int parameter3 = 3;
    
    function(parameter1, parameter2, parameter3);
    
    [self methodWithA:parameter1 b:parameter2 c:parameter3];
    
    [self methodWithX:parameter1 y:parameter2 z:parameter3];
    
}

@end
