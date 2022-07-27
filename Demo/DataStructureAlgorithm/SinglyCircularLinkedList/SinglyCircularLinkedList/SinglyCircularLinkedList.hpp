//
//  SinglyCircularLinkedList.hpp
//  SinglyCircularLinkedList
//
//  Created by lZackx on 2022/7/27.
//

#ifndef SinglyCircularLinkedList_hpp
#define SinglyCircularLinkedList_hpp

#include <stdio.h>
#include <functional>

struct Node {
    int data;
    struct Node *next;
};

class SinglyCircularLinkedList {
public:
    int length;
    struct Node *header;
    
    SinglyCircularLinkedList();
    ~SinglyCircularLinkedList();
    
    struct Node* createNode(int data);
    void addNode(struct Node *node);
    
    struct Node* getNode(int index);
    
    void insertNode(int index, struct Node *node);
    
    void deleteNode(int index);
    void clearNodes();
    
    void traverseNode(std::function<void(int index, struct Node *node)> lambda);
};
#endif /* SinglyCircularLinkedList_hpp */
