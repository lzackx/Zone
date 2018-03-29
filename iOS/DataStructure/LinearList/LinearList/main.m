//
//  main.m
//  LinearList
//
//  Created by lzackx on 2018/3/10.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "array.h"
#import "list.h"

void testArray() {
    
    array *a = array_create(8);
    array_print(a);
    array_destory(a);
}

void testList() {
    
    list *l = list_create();
    list_print(l);
    list_destory(l);
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        
        // array
//        testArray();
        
        // list
        testList();
    }
    return 0;
}
