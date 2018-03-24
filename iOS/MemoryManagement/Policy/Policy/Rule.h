//
//  Rule.h
//  Policy
//
//  Created by lzackx on 2018/3/06.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Rule : NSObject

@property (retain) NSString *example;

- (instancetype)initWithExample:(NSString *)example;

@end
