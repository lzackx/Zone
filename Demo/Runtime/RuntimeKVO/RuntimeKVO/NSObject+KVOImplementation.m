//
//  NSObject+KVOImplementation.m
//  RuntimeKVO
//
//  Created by lzackx on 2018/3/15.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "NSObject+KVOImplementation.h"
#import <objc/message.h>
#import <objc/runtime.h>


@implementation NSObject (KVOImplementation)

static const void *kvo_observer = "kvo_observer";
static const void *kvo_key_path = "kvo_key_path";
static const void *kvo_options = "kvo_options";

- (void)rt_addObserver:(NSObject *)observer
            forKeyPath:(NSString *)keyPath
               options:(NSKeyValueObservingOptions)options
               context:(void *)context {
    
    NSString *originalClassName = NSStringFromClass([self class]);
    NSString *kvoClassName = [NSString stringWithFormat:@"kvo_%@", originalClassName];
    
    
    Class class = objc_allocateClassPair([self class], kvoClassName.UTF8String, 0);
    id value = [observer valueForKeyPath:keyPath];
    /*
     按照例子 只列出了int类型，其他基础类型就不列出来了，原理相同
     需要注意class_addMethod函数中的第一个参数该传递什么值，因为在原类中，是往setter方法发消息，所以为了能被调用，需要正确名称的方法选择器，
     又因为是把self对象设置为了其子类，所以这里是直接添加Setter方法（也就是重写了），而不是利用Method Swizzling把原类的Setter的IMP替换掉。
     */
    char type[4] = "v@:";
    if (strcmp([(NSNumber *)value objCType], @encode(int)) == 0) {
        type[3] = *[(NSNumber *)value objCType];
        class_addMethod(class, NSSelectorFromString([NSString stringWithFormat:@"set%@:", [keyPath capitalizedString]]), (IMP)setInt, type);
    } else {
        type[3] = *[value objCType];
        class_addMethod(class, NSSelectorFromString([NSString stringWithFormat:@"set%@:", [keyPath capitalizedString]]), (IMP)setObject, type);
    }
    objc_registerClassPair(class);
    object_setClass(self, class);
    // 由于category不能新增存储属性，所以用runtime的方式保存好相关信息，便于在observeValueForKeyPath:ofObject:change:context:用上。（实际的实现当然是不需要这样的）
    objc_setAssociatedObject(self, kvo_observer, observer, OBJC_ASSOCIATION_ASSIGN);
    objc_setAssociatedObject(self, kvo_key_path, keyPath, OBJC_ASSOCIATION_ASSIGN);
    objc_setAssociatedObject(self, kvo_options, [NSNumber numberWithUnsignedLong:options], OBJC_ASSOCIATION_ASSIGN);
}

void setInt(id self, SEL _cmd, int i) {
    
    struct objc_super super_struct = {self,class_getSuperclass([self class])};
    objc_msgSendSuper(&super_struct, _cmd, i);
    // 拿回需要用上的信息
    id observer = objc_getAssociatedObject(self, kvo_observer);
    NSString *keyPath = objc_getAssociatedObject(self, kvo_key_path);
    NSUInteger options = [objc_getAssociatedObject(self, kvo_options) unsignedLongValue];
    
    NSMutableDictionary *change = [NSMutableDictionary dictionary];
    // NSKeyValueChangeKindKey的值因为这里的示例只有set，所以也就只把set的类别写死，自定义KVO时，可以根据情况自定义添加更多的信息
    [change addEntriesFromDictionary:@{NSKeyValueChangeKindKey: [NSNumber numberWithInt:NSKeyValueChangeSetting]}];
    // options是以位来记录值的，只列出新值的，原理相同，其他的就不列出来了
    if (options & NSKeyValueObservingOptionNew) {
        [change addEntriesFromDictionary:@{NSKeyValueChangeNewKey: [NSNumber numberWithInt:i]}];
    }
    if (change.count > 0) {
        objc_msgSend(observer,
                     @selector(observeValueForKeyPath:ofObject:change:context:),
                     keyPath,
                     self,
                     change,
                     nil);
    }
}

void setObject(id self, SEL _cmd, id object) {
    
    struct objc_super super_struct = {self,class_getSuperclass([self class])};
    objc_msgSendSuper(&super_struct, _cmd, object);
    // 拿回需要用上的信息
    id observer = objc_getAssociatedObject(self, kvo_observer);
    NSString *keyPath = objc_getAssociatedObject(self, kvo_key_path);
    NSUInteger options = [objc_getAssociatedObject(self, kvo_options) unsignedLongValue];
    NSMutableDictionary *change = [NSMutableDictionary dictionary];
    // NSKeyValueChangeKindKey的值因为这里的示例只有set，所以也就只把set的类别写死，自定义KVO时，可以根据情况自定义添加更多的信息
    [change addEntriesFromDictionary:@{NSKeyValueChangeKindKey: [NSNumber numberWithInt:NSKeyValueChangeSetting]}];
    // options是以位来记录值的，只列出新值的，原理相同，其他的就不列出来了
    if (options & NSKeyValueObservingOptionNew) {
        [change addEntriesFromDictionary:@{NSKeyValueChangeNewKey: object}];
    }
    if (change.count > 0) {
        objc_msgSend(observer,
                     @selector(observeValueForKeyPath:ofObject:change:context:),
                     keyPath,
                     self,
                     change,
                     nil);
    }
}

@end
