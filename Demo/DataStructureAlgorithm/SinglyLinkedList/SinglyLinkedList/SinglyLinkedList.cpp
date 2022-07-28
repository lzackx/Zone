//
//  SinglyLinkedList.cpp
//  SinglyLinkedList
//
//  Created by lZackx on 2022/7/26.
//

#include "SinglyLinkedList.hpp"


// Public
SinglyLinkedList::SinglyLinkedList() {
    header = new Node();
    header->data = 0;
    header->next = nullptr;
}

SinglyLinkedList::~SinglyLinkedList() {
    this->clearNode();
    delete header;
}

bool SinglyLinkedList::empty() {
    if (this->header->next) {
        return false;
    } else {
        return true;
    }
}

int SinglyLinkedList::length() {
    int count = 0;
    if (this->empty()) {
        return count;
    }
    struct Node *currentNode = this->header;
    while (currentNode->next != nullptr) {
        count += 1;
        currentNode = currentNode->next;
    }
    return count;
}

struct Node* SinglyLinkedList::createNode(int data) {
    struct Node *node = new struct Node();
    node->data = data;
    node->next = nullptr;
    return node;
}


void SinglyLinkedList::addNode(struct Node *node) {
    
    // Add from header
//    if (this->header->next) {
//        node->next = this->header->next;
//        this->header->next = node;
//    } else {
//        this->header->next = node;
//    }
    
    // Add from tail
    struct Node *tail = this->header;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = node;
}
struct Node *SinglyLinkedList::getNode(int index) {
    if (index == -1) {
        return this->header;
    }
    if (index < 0 || this->length() <= index) {
        return nullptr;
    }
    struct Node *currentNode = this->header;
    for (int i = 0; i <= index; i++) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

void SinglyLinkedList::insertNode(struct Node *node, int index) {
    if (this->length() < index) {
        return;
    }
    if (node == NULL) {
        return;
    }
    struct Node *prefixNode = this->getNode(index - 1);
    node->next = prefixNode->next;
    prefixNode->next = node;
}

void SinglyLinkedList::deleteNode(int index) {
    if (this->length() < index) {
        return;
    }
    struct Node *prefixNode = this->getNode(index - 1);
    struct Node *targetNode = prefixNode->next;
    prefixNode->next = targetNode->next;
    delete targetNode;
}

void SinglyLinkedList::clearNode() {
    if (this->header->next == nullptr) {
        return;
    }
    struct Node *currentNode = this->header;
    struct Node *lastNode = currentNode;
    int length = this->length();
    for (int i = 0; i < length; i++) {
        lastNode = currentNode;
        currentNode = currentNode->next;
        delete lastNode;
    }
    this->header->next = nullptr;
}

void SinglyLinkedList::traverseNode(std::function<void (struct Node *)> lambda) {
    if (lambda == nullptr) {
        return;
    }
    struct Node *currentNode = this->header;
    int length = this->length();
    for (int i = 0; i < length; i++) {
        currentNode = this->getNode(i);
        lambda(currentNode);
    }
}
