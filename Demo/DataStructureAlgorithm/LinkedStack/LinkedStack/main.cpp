//
//  main.cpp
//  LinkedStack
//
//  Created by lZackx on 2022/8/2.
//

#include <iostream>
#include "LinkedStack.hpp"

void printStack(LinkedStack *stack) {
    std::cout << "count:" << stack->length << "\n[";
    stack->traverseNodes([](int index, struct Node * node) {
        std::cout << node->data;
        if (node->next) {
            std::cout << ", ";
        }
    });
    std::cout << "]\n";
}

int main(int argc, const char * argv[]) {
    
    LinkedStack *stack = new LinkedStack();
    // push
    for (int i = 0; i < 10; i++) {
        struct Node *node = stack->createNode(i);
        stack->pushNode(node);
    }
    printStack(stack);
    
    // pop
    stack->popNode();
    printStack(stack);
    
    // clear
    stack->clearNodes();
    printStack(stack);
    
    return 0;
}
