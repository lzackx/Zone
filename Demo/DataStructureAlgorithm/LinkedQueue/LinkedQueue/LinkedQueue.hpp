//
//  LinkedQueue.hpp
//  LinkedQueue
//
//  Created by lZackx on 2022/8/30.
//

#ifndef LinkedQueue_hpp
#define LinkedQueue_hpp

#include <stdio.h>
#include <functional>

struct Node {
    int data;
    struct Node *next;
};

class LinkedQueue {
public:
    
    Node *header; // Queue Head
    Node *tailer; // Queue Tail
    
    LinkedQueue();
    ~LinkedQueue();
    
    Node *createNode(int data);
    int length();
    bool isEmpty();
    
    void enqueue(Node *data);
    Node* dequeue();
    
    void traverse(std::function<void(Node *data)> lambda);
    
    void clear();
    
};

#endif /* LinkedQueue_hpp */
