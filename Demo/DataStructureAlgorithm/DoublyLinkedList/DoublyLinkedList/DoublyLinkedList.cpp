//
//  DoublyLinkedList.cpp
//  DoublyLinkedList
//
//  Created by lZackx on 2022/7/28.
//

#include "DoublyLinkedList.hpp"



DoublyLinkedList::DoublyLinkedList() {
    this->length = 0;
    this->header = new struct Node();
    this->header->data = 0;
    this->header->previouse = nullptr;
    this->header->next = nullptr;
}

DoublyLinkedList::~DoublyLinkedList() {
    this->clearNodes();
    delete this->header;
}

struct Node* DoublyLinkedList::createNode(int data) {
    struct Node *node = new struct Node();
    node->data = data;
    node->previouse = nullptr;
    node->next = nullptr;
    return node;
}

void DoublyLinkedList::addNode(struct Node *node) {
    struct Node *tail = this->header;
    for (int index = 0; index < this->length; index++) {
        tail = tail->next;
    }
    tail->next = node;
    node->previouse = tail;
    this->length += 1;
}

struct Node* DoublyLinkedList::getNode(int index) {
    if (index == -1) {
        return this->header;
    }
    if (index < 0 || this->length <= index) {
        return nullptr;
    }
    struct Node *targetNode = this->header;
    for (int i = 0; i <= index; i++) {
        targetNode = targetNode->next;
    }
    return targetNode;
}

void DoublyLinkedList::insertNode(int index, struct Node *node) {
    if (index < 0 || this->length < index) {
        return;
    }
    struct Node *previouseNode = this->getNode(index - 1);
    struct Node *nextNode = previouseNode->next;
    
    node->next = nextNode;
    nextNode->previouse = node;
    
    node->previouse = previouseNode;
    previouseNode->next = node;
    
    this->length += 1;
}

void DoublyLinkedList::deleteNode(int index) {
    if (index < 0 || this->length <= index) {
        return;
    }
    struct Node *previousNode = this->getNode(index - 1);
    struct Node *targetNode = previousNode->next;
    struct Node *nextNode = targetNode->next;
    
    previousNode->next = nextNode;
    nextNode->previouse = previousNode;
    
    delete targetNode;
    this->length -= 1;
}

void DoublyLinkedList::clearNodes() {
    
    struct Node *currentNode = this->header;
    struct Node *nextNode = currentNode->next;
    
    for (int index = 0; index < this->length; index++) {
        currentNode = nextNode;
        nextNode = nextNode->next;
        delete currentNode;
    }
    this->length = 0;
}

void DoublyLinkedList::traverseNodes(std::function<void(int index, struct Node *node)> lambda) {
    struct Node *targetNode = this->header;
    for (int i = 0; i < this->length; i++) {
        targetNode = targetNode->next;
        lambda(i, targetNode);
    }
    
}

