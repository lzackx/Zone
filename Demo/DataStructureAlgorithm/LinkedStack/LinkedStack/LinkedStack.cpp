//
//  LinkedStack.cpp
//  LinkedStack
//
//  Created by lZackx on 2022/8/2.
//

#include "LinkedStack.hpp"



LinkedStack::LinkedStack() {
    struct Node *node = new struct Node;
    node->data = 0;
    node->next = nullptr;
    this->header = node;
    this->length = 0;
}

LinkedStack::~LinkedStack() {
    this->clearNodes();
    delete this->header;
}

struct Node* LinkedStack::createNode(int data) {
    struct Node *node = new struct Node;
    node->data = data;
    node->next = nullptr;
    return node;
}

void LinkedStack::pushNode(struct Node *node) {
    struct Node *top = this->header->next;
    
    if (top == nullptr) {
        this->header->next = node;
    } else {
        node->next = top;
        this->header->next = node;
    }
    this->length += 1;
}

struct Node* LinkedStack::popNode() {
    if (this->length <= 0) {
        return nullptr;
    }
    struct Node *top = this->header->next;
    this->header->next = top->next;
    this->length -= 1;
    return top;
}

struct Node* LinkedStack::getNode(int index) {
    if (index < 0 || this->length <= index) {
        return nullptr;
    }
    struct Node *targetNode = this->header;
    for (int index = 0; index < this->length; index++) {
        targetNode = targetNode->next;
    }
    return targetNode;
}

void LinkedStack::clearNodes() {
    struct Node *currentNode = this->header;
    struct Node *nextNode = currentNode->next;
    for (int index = 0; index < this->length; index++) {
        currentNode = nextNode;
        nextNode = nextNode->next;
        delete currentNode;
    }
    this->length = 0;
}

void LinkedStack::traverseNodes(std::function<void(int index, struct Node *node)> lambda) {
    struct Node *node = this->header;
    for (int index = 0; index < this->length; index++) {
        node = node->next;
        if (lambda) {
            lambda(index, node);
        }
    }
}

