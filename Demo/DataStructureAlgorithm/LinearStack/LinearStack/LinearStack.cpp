//
//  LinearStack.cpp
//  LinearStack
//
//  Created by lZackx on 2022/8/2.
//

#include "LinearStack.hpp"



LinearStack::LinearStack(int capacity) {
    this->capacity = capacity;
    this->data = (int *)calloc(capacity, sizeof(int));
    this->top = -1;
}

LinearStack::~LinearStack() {
    this->top = 0;
    free(this->data);
    this->capacity = 0;
}

void LinearStack::push(int data) {
    
    if (this->top >= this->capacity) {
        return;
    }
    this->top += 1;
    this->data[this->top] = data;
}

int LinearStack::pop() {
    if (this->top < 0) {
        return NULL;
    }
    int data = this->data[this->top];
    this->top -= 1;
    
    return data;
}

int LinearStack::get() {
    int data = this->data[this->top];
    return data;
}

void LinearStack::traverse(std::function<void(int index, int data)> lambda) {
    for (int index = this->top; 0 <= index ; index--) {
        int data = this->data[index];
        if (lambda != nullptr) {
            lambda(index, data);
        }
    }
}

