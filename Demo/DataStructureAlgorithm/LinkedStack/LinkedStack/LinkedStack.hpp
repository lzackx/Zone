//
//  LinkedStack.hpp
//  LinkedStack
//
//  Created by lZackx on 2022/8/2.
//

#ifndef LinkedStack_hpp
#define LinkedStack_hpp

#include <stdio.h>
#include <functional>

struct Node {
    int data;
    struct Node *next;
};

class LinkedStack {
public:
    int length;
    struct Node *header;
    
    LinkedStack();
    ~LinkedStack();
    
    struct Node* createNode(int data);
    
    void pushNode(struct Node *node);
    struct Node *popNode();
    
    struct Node* getNode(int index);
    
    void clearNodes();
    
    void traverseNodes(std::function<void(int index, struct Node *node)> lambda);
    
};


#endif /* LinkedStack_hpp */
