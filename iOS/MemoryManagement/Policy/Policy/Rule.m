//
//  Rule.m
//  Policy
//
//  Created by lzackx on 2018/3/06.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "Rule.h"

@interface Rule ()

@end

@implementation Rule

// 这里显式声明@property会做的操作
@synthesize example = _example;
- (NSString *)example {
    
    // 因为返回的是是synthesize对象，所以不需要retain或release
    return _example;
}
- (void)setExample:(NSString *)example {
    
    /*
     显然，要让synthesize对象保留参数对象，
     那么就要先拔参数传递过来的对象保留拥有权，并把旧的对象释放掉
     */
    [example retain];
    [_example release];
    _example = example;
}

- (instancetype)initWithExample:(NSString *)example {
    self = [super init];
    if (self) {
        // 在init方法里，不要使用访问器方法。
        _example = [NSString string];
    }
    return self;
}

- (void)dealloc {
    
    // 在dealloc方法里，不要使用访问器方法。
    [_example release];
    [super dealloc];
}

- (NSString *)rule {
    
    /*
     [NSString string]是工程方法，依照规则，它没有保留对象的拥有权，所以没问题。
     */
    NSString *r = [NSString string];
    
    /*
     [[NSString alloc] init]
     创建了一个对象，依照规则，它保留对象的拥有权。
     在MRC中，堆中创建了空间后，没有释放，就会出现内存泄漏。
     
    NSString *r = [[NSString alloc] init];
     */
    /*
     [[[NSString alloc] init] autorelease]
     创建了一个对象后，依照规则，它保留对象的拥有权，
     而在后面使用了autorelease，那么在使用完毕后，堆中开辟的内存就会释放，不会出现内存泄漏问题。
     这里要注意的是，用autorelease而不是release是因为这里需要作为返回值，
     而autorelease能允许方法在返回对象前，不释放对象。
     
    NSString *r = [[[NSString alloc] init] autorelease];
     */
    
    /*
     这里要注意的是error对象，它并不是由[NSString alloc]初始化的，它的初始化在方法内部，
     所以这个error对象并不需要在这里释放。
     
    NSError *error;
    NSString *r = [[[NSString alloc] initWithContentsOfFile:@"" encoding:NSUTF8StringEncoding error:&error] autorelease];
     */
    
    
    return r;
}

@end
