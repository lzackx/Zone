//
//  list.h
//  LinearList
//
//  Created by lzackx on 2018/3/10.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#ifndef list_h
#define list_h

#include <stdio.h>
/*
 .c源码中因经过list_private.h的封装，所以已经有LIST类型的声明，
 但在这头文件中，因为有相关函数的声明，所以相应地，在没有宏定义的这个文件中，
 可以简单声明，使编译期间不报错，但其实在编译器链接时，起作用的还是私有头文件中的声明。
 */
#ifndef LIST
typedef void list;
typedef void list_node;
typedef void * list_node_value;
#endif

list* list_create(void);
list_node* list_node_create(list_node_value lnv);
void list_clear(list *l);
void list_destory(list *l);
int list_get_length(list *l);
list_node* list_node_get(list *l, int index);
list_node_value list_node_get_value(list_node *ln);
void list_node_value_insert(list *l, int index, list_node_value *nln);
void list_node_value_add(list *l, list_node_value *ln);
void list_node_set(list *l, int index, list_node *nln);
void list_node_set_value(list_node *ln, list_node_value lnv);
void list_node_remove(list *l, int index);
void list_node_value_remove(list *l, list_node_value lnv);
void list_print(list *l);

#endif /* list_h */
