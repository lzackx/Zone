//
//  LinearStack.hpp
//  LinearStack
//
//  Created by lZackx on 2022/8/2.
//

#ifndef LinearStack_hpp
#define LinearStack_hpp

#include <stdio.h>
#include <functional>

class LinearStack {
public:
    int capacity;
    int *data;
    int top;
    
    LinearStack(int capacity);
    ~LinearStack();
    
    int length();
    
    void push(int data);
    int pop();
    
    int get();
    
    void traverse(std::function<void(int index, int data)> lambda);
    
    void clear();
    
};

#endif /* LinearStack_hpp */
