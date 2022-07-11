//
//  ViewController.m
//  FFmpeg
//
//  Created by lzackx on 2018/4/2.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"
#import "FFmpegTest.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    [FFmpegTest test];
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
