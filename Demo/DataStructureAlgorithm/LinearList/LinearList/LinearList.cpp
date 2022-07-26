//
//  LinearList.cpp
//  LinearList
//
//  Created by lZackx on 2022/7/26.
//

#include "LinearList.hpp"


LinearList::LinearList(int count) {
    this->data = (int *)calloc(count, sizeof(int));
    this->length = 0;
    this->maxLength = count;
}

LinearList::~LinearList() {
    this->length = 0;
    this->maxLength = 0;
    free(this->data);
}

bool LinearList::empty() {
    if (this->length == 0) {
        return true;
    }
    return false;
}

void LinearList::addData(int data) {
    if (this->length == this->maxLength) {
        return;
    }
    this->data[this->length] = data;
    this->length += 1;
}

void LinearList::insertData(int index, int data) {
    if (index < 0 || this->maxLength <= (index + 1)) {
        return;
    }
    for (int i = (this->length - 1); i >= index ; i--) {
        this->data[i+1] = this->data[i];
    }
    this->data[index] = data;
    this->length += 1;
}

int LinearList::getData(int index) {
    if (index < 0 || this->length <= index) {
        return -1;
    }
    return this->data[index];
}

void LinearList::deleteData(int index) {
    if (index < 0 || this->length <= index) {
        return;
    }
    for (int i = index; i < this->length; i++) {
        this->data[i] = this->data[i+1];
    }
    this->length -= 1;
}

void LinearList::clearData() {
    this->length = 0;
}

void LinearList::traverseData(std::function<void(int index, int data)> lambda) {
    for (int index = 0; index < this->length; index++) {
        if (lambda) {
            lambda(index, this->data[index]);
        }
    }
}
