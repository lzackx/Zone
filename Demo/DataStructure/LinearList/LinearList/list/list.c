//
//  list.c
//  LinearList
//
//  Created by lzackx on 2018/3/10.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#include "list_private.h"
#include "list.h"
#include <stdlib.h>
#include "string.h"

// 创建
list* list_create() {
    
    list *l = malloc(sizeof(list) + sizeof(list_node));
    if (l) {
        l->length = 0;
        l->header = (list_node *)(l + 1);
        /*
         这里有个比容易中但较难发现的坑，初始化时，需要把header内的next指向显式指定为NULL，
         如果没有这步，因为内存中可能会存在莫名其妙的值，
         会导致链表的最后一个node的指向认为这个值是个指针，最后访问错误导致crash。
         */
        l->header->next = NULL;
    }
    return l;
}

list_node* list_node_create(list_node_value lnv) {
    
    list_node *ln = malloc(sizeof(list_node));
    if (ln == NULL) {
        return NULL;
    }
    ln->next = NULL;
    ln->value = lnv;
    return ln;
}

// 清除
void list_clear(list *l) {
    
    if (l == NULL) {
        return;
    }
    list_node *lhn = l->header;
    while (lhn) {
        list_node *lnn = lhn->next;
        if (lnn == NULL) {
            break;
        }
        lhn->next = lnn->next;
        free(lnn);
    }
    l->length = 0;
}

// 销毁：链表中，因为存储结构的不连续，导致清除数据需要把每个node都拿出来free掉。
void list_destory(list *l) {
    
    if (l == NULL) {
        return;
    }
    list_clear(l);
    free(l);
    l = NULL;
}


// 获取长度
int list_get_length(list *l) {
    
    if (l == NULL) {
        return 0;
    }
    return l->length;
}

list_node* list_node_get(list *l, int index) {
    
    if (l == NULL) {
        return NULL;
    }
    list_node *ln = l->header;
    for (int i = 0; i < index; i++) {
        ln = ln->next;
    }
    
    return ln;
}

list_node_value list_node_get_value(list_node *ln) {
    
    if (ln == NULL) {
        return NULL;
    }
    return ln->value;
}

// 插入：注意指针操作
void list_node_value_insert(list *l, int index, list_node_value *lnv) {
    
    if (l == NULL || index < 0 || index > l->length) {
        return;
    }

    list_node *nln = malloc(sizeof(list_node));
    if (nln == NULL) {
        return;
    }
    nln->next = NULL;
    nln->value = lnv;
    
    list_node *ln = l->header;
    for (int i = 0;i < index;i++) {
        ln = ln->next;
    }
    nln->next = ln->next;
    ln->next = nln;
    l->length += 1;
}

// 增加：等同于末尾插入
void list_node_value_add(list *l, list_node_value *lnv){
    
    if (l == NULL) {
        return;
    }
    
    list_node_value_insert(l, l->length, lnv);
}

// 修改
void list_node_set(list *l, int index, list_node *nln) {
    if (l == NULL || nln == NULL) {
        return;
    }
    list_node *ln = l->header;
    for (int i = 0; i <= index; i++) {
        ln = ln->next;
    }
    nln->next = ln->next;
    free(ln->next);
    ln->next = nln;
}

void list_node_set_value(list_node *ln, list_node_value lnv) {
    if (ln == NULL) {
        return;
    }
    ln->value = lnv;
}

// 删除
void list_node_remove(list *l, int index) {
    
    if (l == NULL || l->length <= index || index < 0) {
        return;
    }
    list_node *ln = l->header;
    for (int i = 0;i < index; i++) {
        ln = ln->next;
    }
    list_node *rln = ln->next;
    ln->next = rln->next;
    free(rln);
    rln = NULL;
    l->length -= 1;
}

void list_node_value_remove(list *l, list_node_value lnv) {
    
    if (l == NULL || l->length < 0) {
        return;
    }
    
    list_node *ln = l->header;
    while (ln) {
        list_node *lnn = ln->next;
        if (lnn == NULL) {
            return;
        }
        if (lnn->value == lnv) {
            ln->next = lnn->next;
            free(lnn);
            lnn = NULL;
            l->length -= 1;
        } else {
            ln = lnn;
        }
    }
    
}

// 打印
void list_print(list *l) {
    
    printf("list\n");
    printf("{\n");
    printf("\tlength: %d\n", l->length);
    printf("\tvalue: [");
    list_node *ln = l->header;
    for (int i = 0; i < l->length; i++) {
        ln = ln->next;
        printf("%p", (ln->value));
        if (i < l->length - 1) {
            printf(",");
        }
    }
    printf("]\n}\n");
}
