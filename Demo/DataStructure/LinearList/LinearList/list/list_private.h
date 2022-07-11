//
//  list_private.h
//  LinearList
//
//  Created by lzackx on 2018/3/28.
//  Copyright © 2018年 lzackx. All rights reserved.
//

/*
 这是一个私有头文件，目的是为了封装结构体内的变量，使外部调用时，无法直接访问修改。
 #define LIST
 这个宏是重点。
 */

#ifndef list_private_h
#define list_private_h

//typedef void * list_node;
typedef void * list_node_value;

typedef struct _list_node list_node;
struct _list_node {
    
    list_node_value value;
    list_node *next;
    
};

typedef struct {
    
    int length;
    list_node *header;
    
} list;


#define LIST

#endif /* list_private_h */

