//
//  DoublyLinkedList.hpp
//  DoublyLinkedList
//
//  Created by lZackx on 2022/7/28.
//

#ifndef DoublyLinkedList_hpp
#define DoublyLinkedList_hpp

#include <stdio.h>
#include <functional>

struct Node {
    int data;
    struct Node *previouse;
    struct Node *next;
};

class DoublyLinkedList {
public:
    int length;
    struct Node *header;
    
    DoublyLinkedList();
    ~DoublyLinkedList();
    
    struct Node* createNode(int data);
    
    void addNode(struct Node *node);
    
    struct Node *getNode(int index);
    
    void insertNode(int index, struct Node *node);
    
    void deleteNode(int index);
    
    void clearNodes();
    
    void traverseNodes(std::function<void(int index, struct Node *node)> lambda);
};

#endif /* DoublyLinkedList_hpp */
