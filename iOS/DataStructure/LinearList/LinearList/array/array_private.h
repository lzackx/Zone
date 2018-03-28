//
//  array_private.h
//  LinearList
//
//  Created by lzackx on 2018/3/10.
//  Copyright © 2018年 lzackx. All rights reserved.
//

/*
 这是一个私有头文件，目的是为了封装结构体内的变量，使外部调用时，无法直接访问修改。
 #define ARRAY
 这个宏是重点。
 */

#ifndef array_private_h
#define array_private_h

typedef void * array_value;

typedef struct {
    
    int capacity;
    int length;
    array_value *value;
    
} array;
#define ARRAY

#endif /* array_private_h */
