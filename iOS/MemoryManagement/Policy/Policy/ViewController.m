//
//  ViewController.m
//  Policy
//
//  Created by lzackx on 2018/3/06.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property Rule *rule;

@end

@implementation ViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.rule = [[Rule alloc] initWithExample:@""];
    
    self.rule.example = @"Example";
    NSLog(@"example: %@", self.rule.example);
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc {

    [self.rule release];
    
    [super dealloc];
}


@end
