//
//  MessagingObject.m
//  Message
//
//  Created by lzackx on 2018/3/15.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "MessagingObject.h"
#import <objc/message.h>
#import "SurrogateObject.h"


@interface MessagingObject ()

@property SurrogateObject *surrogateObject;

@end

@implementation MessagingObject

- (instancetype)init
{
    self = [super init];
    if (self) {
        
        _surrogateObject = [SurrogateObject new];
        NSLog(@"self class: %@, super class: %@", [self class], [super class]);
        // self class: MessagingObject, super class: MessagingObject
    }
    return self;
}
// - MARK: messaging
- (void)methodWithParameter:(NSString *)parameter {
    
    NSLog(@"Parameter: %@", parameter);
}

// - MARK: dynamic method
void dynamicMethodIMP(id self, SEL _cmd) {
    
    NSLog(@"dynamicMethodIMP called");
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundeclared-selector"
+ (BOOL)resolveInstanceMethod:(SEL)sel {
    if (sel == @selector(dynamicMethodIMP)) {
        class_addMethod([self class], sel, (IMP)dynamicMethodIMP, "v@:");
        return YES;
    }
    return [super resolveInstanceMethod:sel];
}
#pragma clang diagnostic pop

// - MARK: massaging forwarding
- (id)forwardingTargetForSelector:(SEL)aSelector {
    
    return [super forwardingTargetForSelector:aSelector];
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector {
    
    NSMethodSignature *methodSignature = [super methodSignatureForSelector: aSelector];
    if (!methodSignature) {
        methodSignature = [self.surrogateObject methodSignatureForSelector:aSelector];
    }
    return methodSignature;
}

- (void)forwardInvocation:(NSInvocation *)anInvocation {
    
    if ([self respondsToSelector: [anInvocation selector]]) {
        [anInvocation invokeWithTarget:self];
    } else if ([self.surrogateObject respondsToSelector:[anInvocation selector]]) {
        [anInvocation invokeWithTarget:self.surrogateObject];
    } else {
        [super forwardInvocation:anInvocation];
    }
    
}

@end










