//
//  SinglyCircularLinkedList.cpp
//  SinglyCircularLinkedList
//
//  Created by lZackx on 2022/7/27.
//

#include "SinglyCircularLinkedList.hpp"



SinglyCircularLinkedList::SinglyCircularLinkedList() {
    this->length = 0;
    this->header = new struct Node();
    this->header->data = 0;
    this->header->next = nullptr;
}

SinglyCircularLinkedList::~SinglyCircularLinkedList() {
    this->length = 0;
    delete this->header;
}

struct Node* SinglyCircularLinkedList::createNode(int data) {
    struct Node *node = new struct Node();
    node->data = data;
    node->next = nullptr;
    return node;
}

void SinglyCircularLinkedList::addNode(struct Node *node) {
    struct Node *tailNode = this->header;
    for (int index = 0; index < this->length; index++) {
        tailNode = tailNode->next;
    }
    tailNode->next = node;
    node->next = this->header;
    this->length += 1;
}

struct Node* SinglyCircularLinkedList::getNode(int index) {
    if (index < 0 || this->length <= index) {
        return nullptr;
    }
    struct Node *currentNode = this->header;
    for (int i = 0; i <= index; i++) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

void SinglyCircularLinkedList::insertNode(int index, struct Node *node) {
    if (index < 0 || this->length < index) {
        return;
    }
    struct Node *previousNode = nullptr;
    if ((index - 1) < 0) { // index is first valid node
        previousNode = this->getNode(this->length - 1);
    } else {
        previousNode = this->getNode(index - 1);
    }
    struct Node *nextNode = previousNode->next;
    node->next = nextNode;
    previousNode->next = node;
    this->length += 1;
}

void SinglyCircularLinkedList::deleteNode(int index) {
    if (index < 0 || this->length <= index) {
        return;
    }
    struct Node *previousNode = nullptr;
    if ((index - 1) < 0) { // index is first valid node
        previousNode = this->getNode(this->length - 1);
        this->header->next = this->getNode(1);
    } else {
        previousNode = this->getNode(index - 1);
    }
    struct Node *targetNode = previousNode->next;
    
    previousNode->next = targetNode->next;
    delete targetNode;
    this->length -= 1;
}

void SinglyCircularLinkedList::clearNodes() {
    if (this->length == 0) {
        return;
    }
    struct Node *currentNode = this->header;
    struct Node *nextNode = currentNode->next;
    for (int index = 0; index < this->length; index++) {
        currentNode = nextNode;
        nextNode = nextNode->next;
        delete currentNode;
    }
    this->length = 0;
}

void SinglyCircularLinkedList::traverseNode(std::function<void(int index, struct Node *node)> lambda) {
    struct Node *currentNode = this->header;
    for (int i = 0; i < this->length; i++) {
        currentNode = currentNode->next;
        lambda(i, currentNode);
    }
}

