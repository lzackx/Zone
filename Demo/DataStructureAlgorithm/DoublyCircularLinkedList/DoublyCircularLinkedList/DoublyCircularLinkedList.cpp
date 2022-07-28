//
//  DoublyCircularLinkedList.cpp
//  DoublyCircularLinkedList
//
//  Created by lZackx on 2022/7/28.
//

#include "DoublyCircularLinkedList.hpp"



DoublyCircularLinkedList::DoublyCircularLinkedList() {
    this->length = 0;
    this->header = new struct Node();
    this->header->data = 0;
    this->header->previous = nullptr;
    this->header->next = nullptr;
}

DoublyCircularLinkedList::~DoublyCircularLinkedList() {
    this->clearNodes();
    delete this->header;
}

struct Node* DoublyCircularLinkedList::createNode(int data) {
    struct Node *node = new struct Node();
    node->data = data;
    node->previous = nullptr;
    node->next = nullptr;
    return node;
}

void DoublyCircularLinkedList::addNode(struct Node *node) {
    struct Node *tail = this->header;
    for (int index = 0; index < this->length; index++) {
        tail = tail->next;
    }
    node->previous = tail;
    tail->next = node;
    
    node->next = this->header->next;
    this->header->next->previous = node;
    
    this->length += 1;
}

struct Node* DoublyCircularLinkedList::getNode(int index) {
    if (index == -1) {
        return this->header;
    }
    if (index < 0 || this->length <= index) {
        return nullptr;
    }
    struct Node *targetNode = this->header;
    for (int i = 0; i < index; i++) {
        targetNode = targetNode->next;
    }
    return targetNode;
}

void DoublyCircularLinkedList::insertNode(int index, struct Node *node) {
    if (index < 0 || this->length < index) {
        return;
    }
    struct Node *previousNode = this->getNode(index - 1);
    struct Node *nextNode = previousNode->next;
    
    node->next = nextNode;
    nextNode->previous = node;
    
    node->previous = previousNode;
    previousNode->next = node;
    
    this->length += 1;
}

void DoublyCircularLinkedList::deleteNode(int index) {
    if (index < 0 || this->length <= index) {
        return;
    }
    struct Node *previouseNode = this->getNode(index - 1);
    struct Node *targetNode = previouseNode->next;
    struct Node *nextNode = targetNode->next;
    
    previouseNode->next = nextNode;
    nextNode->previous = previouseNode;
    
    delete targetNode;
    
    this->length -= 1;
}

void DoublyCircularLinkedList::clearNodes() {
    struct Node *currentNode = this->header;
    struct Node *nextNode = currentNode->next;
    for (int index = 0; index < this->length;index++) {
        currentNode = nextNode;
        nextNode = nextNode->next;
        delete currentNode;
    }
    this->length = 0;
}

void DoublyCircularLinkedList::traverseNodes(std::function<void(int index, struct Node *node)> lambda) {
    
    struct Node *node = this->header;
    for (int index = 0; index < this->length; index++) {
        node = node->next;
        lambda(index, node);
    }
    
}

