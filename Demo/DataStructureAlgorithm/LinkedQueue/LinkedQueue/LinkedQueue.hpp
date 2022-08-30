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

class LinkedQueue {
public:
    
    int *header;
    int *tailer;
    
    LinkedQueue(int capacity);
    ~LinkedQueue();
    
    int length();
    
    bool isEmpty();
    
    int get(int index);
    
    void enqueue(int data);
    int dequeue();
    
    void traverse(std::function<void(int index, int data)> lambda);
    
    void clear();
    
};

#endif /* LinkedQueue_hpp */
