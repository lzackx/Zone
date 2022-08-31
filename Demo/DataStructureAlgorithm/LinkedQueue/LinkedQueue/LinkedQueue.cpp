//
//  LinkedQueue.cpp
//  LinkedQueue
//
//  Created by lZackx on 2022/8/30.
//

#include "LinkedQueue.hpp"



LinkedQueue::LinkedQueue() {
    struct Node *headerNode = new struct Node();
    this->header = headerNode;
    struct Node *tailerNode = new struct Node();
    this->tailer = tailerNode;
}

LinkedQueue::~LinkedQueue() {
    free(this->header);
    free(this->tailer);
}

struct Node* LinkedQueue::createNode(int data) {
    struct Node *node = new struct Node();
    node->data = data;
    return node;
}

int LinkedQueue::length() {
    int length = 0;
    if (this->isEmpty() == false) {
        struct Node *currentNode = this->header;
        while (currentNode->next) {
            length++;
            currentNode = currentNode->next;
        }
    }
    return length;
}

bool LinkedQueue::isEmpty() {
    bool isEmpty = true;
    if (this->header->next != nullptr) {
        isEmpty = false;
    }
    return isEmpty;
}

void LinkedQueue::enqueue(struct Node *data) {
    if (this->header->next == nullptr) {
        this->header->next = data;
    }
    
    if (this->tailer->next) {
        struct Node *lastNode = this->tailer->next;
        lastNode->next = data;
    }
    this->tailer->next = data;
}

struct Node* LinkedQueue::dequeue() {
    if (this->isEmpty()) {
        return nullptr;
    }
    struct Node *firstNode = this->header->next;
    this->header->next = firstNode->next;
    return firstNode;
}

void LinkedQueue::traverse(std::function<void(struct Node *data)> lambda) {
    if (this->isEmpty()) {
        return;
    }
    struct Node *currentNode = this->header;
    while (currentNode->next) {
        currentNode = currentNode->next;
        if (lambda) {
            lambda(currentNode);
        }
    }
}

void LinkedQueue::clear() {
    this->header = nullptr;
    this->tailer = this->header;
}

