//
//  SinglyLinkedList.hpp
//  SinglyLinkedList
//
//  Created by lZackx on 2022/7/26.
//

#ifndef SinglyLinkedList_hpp
#define SinglyLinkedList_hpp

#include <stdio.h>
#include <functional>

struct Node {
    int data;
    struct Node *next;
};

class SinglyLinkedList {

public:
    struct Node *header;
    
    SinglyLinkedList();
    ~SinglyLinkedList();
    
    bool empty();
    int length();
    
    struct Node* createNode(int data);
    void addNode(struct Node *node);
    
    struct Node *getNode(int index);
    void insertNode(struct Node *node, int index);
    void deleteNode(int index);
    void clearNode();
    
    int indexOfNode(struct Node *node);
    
    void traverseNode(std::function<void(struct Node *)> lambda);
    
};


#endif /* SinglyLinkedList_hpp */
