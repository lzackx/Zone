//
//  LinearQueue.cpp
//  LinearQueue
//
//  Created by lZackx on 2022/8/30.
//

#include "LinearQueue.hpp"


LinearQueue::LinearQueue(int capacity) {
    this->capacity = capacity;
    this->data = (int *)calloc(capacity, sizeof(int));
    this->header = 0;
    this->tailer = 0;
}

LinearQueue::~LinearQueue() {
    this->header = 0;
    this->tailer = 0;
    free(this->data);
    this->capacity = 0;
}

int LinearQueue::length() {
    int length = (this->tailer - this->header + this->capacity) % this->capacity;
    return length;
}

bool LinearQueue::isEmpty() {
    bool isEmpty = false;
    if (this->header == this->tailer) {
        isEmpty = true;
    }
    return isEmpty;
}

bool LinearQueue::isFull() {
    bool isFull = false;
    if (this->header == ((this->tailer + 1) % this->capacity)) {
        isFull = true;
    }
    return isFull;
}

int LinearQueue::get(int index) {
    int data = this->data[index];
    return data;
}

void LinearQueue::enqueue(int data) {
    if (this->isFull()) {
        return;
    }
    this->data[this->tailer] = data;
    this->tailer = (this->tailer + 1) % this->capacity;
}

int LinearQueue::dequeue() {
    if (this->isEmpty()) {
        return 0;
    }
    int data = this->data[this->header];
    this->header = (this->header + 1) % this->capacity;
    return data;
}

void LinearQueue::traverse(std::function<void(int index, int data)> lambda) {
    int index = this->header;
    while (index != this->tailer) {
        
        if (lambda) {
            int data = this->get(index);
            lambda(index, data);
        }
        index = (index + 1) % this->capacity;
    }
}

void LinearQueue::clear() {
    this->tailer = this->header = 0;
}

