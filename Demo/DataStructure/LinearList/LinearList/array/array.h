//
//  array.h
//  LinearList
//
//  Created by lzackx on 2018/3/10.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#ifndef array_h
#define array_h

#include <stdio.h>

/*
 .c源码中因经过array_private.h的封装，所以已经有array类型的声明，
 但在这头文件中，因为有相关函数的声明，所以相应地，在没有ARRAY宏定义的这个文件中，
 可以简单声明，使编译期间不报错，但其实在编译器链接时，起作用的还是私有头文件中的声明。
 */
#ifndef ARRAY
typedef void array;
typedef void * array_value;
#endif

array *array_create(int capacity);
void array_destory(array *a);
void array_clear(array *a);
int array_get_length(array *a);
array_value array_get_value(array *a, int index);
void array_insert(array *a, int index, array_value av);
void array_add(array *a, array_value av);
void array_set_value(array *a, int index, array_value av);
void array_remove(array *a, int index);
void array_remove_value(array *a, array_value av);
void array_print(array *a);

#endif /* array_h */
