//
//  main.cpp
//  LinearStack
//
//  Created by lZackx on 2022/8/2.
//

#include <iostream>
#include "LinearStack.hpp"


void printStack(LinearStack *list) {
    std::cout << "top:" << list->top << "\n[";
    list->traverse([&](int index, int data) {
        std::cout << data;
        if (index < list->capacity && 0 < index) {
            std::cout << ", ";
        }
    });
    std::cout << "]\n";
}

int main(int argc, const char * argv[]) {
    
    
    LinearStack *stack = new LinearStack(10);
    printStack(stack);
    
    // push
    for (int i = 0; i < stack->capacity; i++) {
        stack->push(i);
    }
    printStack(stack);

    
    // delete
    int data = stack->pop();
    std::cout << "pop: " << data << "\n";
    printStack(stack);
        
    return 0;
}
