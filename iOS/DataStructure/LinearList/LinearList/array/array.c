//
//  array.c
//  LinearList
//
//  Created by lzackx on 2018/3/10.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#include "array_private.h"
#include "array.h"
#include <stdlib.h>
#include "string.h"

// 创建
array *array_create(int capacity) {
    
    if (capacity < 0) {
        return NULL;
    }
    array *a = malloc(sizeof(array));
    if (a) {
        a->capacity = capacity;
        a->length = 0;
        a->value = capacity ? malloc(sizeof(array_value) * capacity) : NULL;
    }
    return a;
}

/* 销毁
 销毁过程需要注意对应创建过程，由于创建过程中，a->value与a的开辟内存堆空间是分开的，
 所以在销毁过程，要分步释放内存堆空间，防止内存泄漏。
 */
void array_destory(array *a) {
    
    if (a == NULL) {
        return;
    }
    free(a->value);
    free(a);
}

/* 清除
 清除过程并不是把内存中的数据擦除，而是让内存知道旧数据不可用就可以了。
 */
void array_clear(array *a) {
    
    if (a == NULL) {
        return;
    }
    a->length = 0;
}

// 获取长度
int array_get_length(array *a) {
    
    if (a == NULL) {
        return 0;
    }
    return a->length;
}

// 获取值：注意别越界
array_value array_get_value(array *a, int index) {
    
    if (a == NULL || index < 0 || index >= a->length) {
        return NULL;
    }
    // 皆为指针的使用 等同于 *((a->value)+index)
    return a->value[index];
}

/* 插入
 当数组可扩容时，步骤如下：
 1. 当堆空间容量不够了，就重新malloc一块新空间，该空间容量按不同的规则而不同，这里示范2倍空间。
 2. 复制旧数据到新数堆空间
 3. 将旧空间释放掉，不需要做擦除
 */
void array_insert(array *a, int index, array_value av) {
    
    if (a == NULL || index < 0 || index > a->length) {
        return;
    }
    // 数组空间满时
    if (a->capacity == a->length) {
        int newCapacity = a->capacity * 2; //2倍旧空间大小，就是扩大一倍空间
        array_value newValue = malloc(sizeof(array_value) * newCapacity);
        if (newValue == NULL) {
            return; // 堆空间分配失败，就只能返回了
        }
        /*
         直接使用内存复制比较方便(不然就得for循环逐条复制了)，
         意思是将旧内存 a->value 的 sizeof(array_value) * a->length 那么多字节，
         复制到 newValue 内存里
         */
        memcpy(newValue, a->value, sizeof(array_value) * a->length);
        // 最后就是释放旧的，保留新的，并更新新容量
        free(a->value);
        a->value = newValue;
        a->capacity = newCapacity;
    }
    
    for (int i = a->length;i > index;i--) {
        a->value[i + 1] = a->value[i];
    }
    a->value[index] = av;
    a->length += 1;
}

// 增加：等同于末尾插入
void array_add(array *a, array_value av) {
    
    if (a == NULL) {
        return;
    }
    
    array_insert(a, a->length, av);
}

// 修改
void array_set_value(array *a, int index, array_value av) {
    if (a == NULL) {
        return;
    }
    a->value[index] = av;
}

// 删除
void array_remove(array *a, int index) {
    
    if (a == NULL || a->length <= index || index < 0) {
        return;
    }
    
    for (int i = index;i < a->length; i++) {
        a->value[i] = a->value[i + 1];
    }
    a->length -= 1;
}

// 删除
void array_remove_value(array *a, array_value av) {
    
    if (a == NULL) {
        return;
    }
    int count = 0;
    for (int i = 0; i < a->length; i++) {
        if (a->value[i] == av) {
            count++;
        } else {
            a->value[i - count] = a->value[i];
        }
    }
    a->length -= count;
}

// 打印
void array_print(array *a) {
    
    printf("array\n");
    printf("{\n");
    printf("\tcapacity: %d\n", a->capacity);
    printf("\tlength: %d\n", a->length);
    printf("\tvalue: [");
    for (int i = 0; i < a->length; i++) {
        printf("%p", *(a->value));
        if (i < a->length - 1) {
            printf(",");
        }
    }
    printf("]\n}\n");
}







