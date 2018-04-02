//
//  FFmpegTest.m
//  FFmpeg
//
//  Created by lzackx on 2018/4/2.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "FFmpegTest.h"
#import "avcodec.h"

@implementation FFmpegTest

+ (void)test {
    
    NSLog(@"%@", [NSString stringWithUTF8String:avcodec_configuration()]);
    
}

@end
