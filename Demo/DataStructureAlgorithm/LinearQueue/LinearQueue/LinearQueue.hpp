//
//  LinearQueue.hpp
//  LinearQueue
//
//  Created by lZackx on 2022/8/30.
//

#ifndef LinearQueue_hpp
#define LinearQueue_hpp

#include <stdio.h>
#include <functional>

class LinearQueue {
public:
    
    int capacity;
    int *data;
    int header;
    int tailer;
    
    LinearQueue(int capacity);
    ~LinearQueue();
    
    int length();
    
    bool isEmpty();
    bool isFull();
    
    int get(int index);
    
    void enqueue(int data);
    int dequeue();
    
    void traverse(std::function<void(int index, int data)> lambda);
    
    void clear();    
    
};


#endif /* LinearQueue_hpp */
