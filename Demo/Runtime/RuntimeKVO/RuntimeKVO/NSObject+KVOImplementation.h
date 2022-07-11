//
//  NSObject+KVOImplementation.h
//  RuntimeKVO
//
//  Created by lzackx on 2018/3/15.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSObject (KVOImplementation)

- (void)rt_addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(void *)context;

@end
