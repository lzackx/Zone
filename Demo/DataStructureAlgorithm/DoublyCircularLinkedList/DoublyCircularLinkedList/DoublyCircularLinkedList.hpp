//
//  DoublyCircularLinkedList.hpp
//  DoublyCircularLinkedList
//
//  Created by lZackx on 2022/7/28.
//

#ifndef DoublyCircularLinkedList_hpp
#define DoublyCircularLinkedList_hpp

#include <stdio.h>
#include <functional>

struct Node {
    int data;
    struct Node *previous;
    struct Node *next;
};

class DoublyCircularLinkedList {
public:
    int length;
    struct Node *header;

    DoublyCircularLinkedList();
    ~DoublyCircularLinkedList();
    
    struct Node *createNode(int data);
    
    void addNode(struct Node *node);
    
    struct Node *getNode(int index);
    
    void insertNode(int index, struct Node *node);
    
    void deleteNode(int index);
    
    void clearNodes();
    
    void traverseNodes(std::function<void(int index, struct Node *node)> lambda);
    
};


#endif /* DoublyCircularLinkedList_hpp */
