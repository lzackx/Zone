//
//  main.cpp
//  LinearQueue
//
//  Created by lZackx on 2022/8/30.
//

#include <iostream>
#include "LinearQueue.hpp"


void printStack(LinearQueue *list) {
    std::cout << "length:" << list->length() << "\n[";
    list->traverse([&](int index, int data) {
        std::cout << data;
        if (index < (list->tailer - 1)) {
            std::cout << ", ";
        }
    });
    std::cout << "]\n";
}

int main(int argc, const char * argv[]) {
    
    LinearQueue *queue = new LinearQueue(10);
    printStack(queue);

    // enqueue
    for (int i = 0; i < queue->capacity; i++) {
        queue->enqueue(i);
    }
    printStack(queue);


    // delete
    int data = queue->dequeue();
    std::cout << "dequeue: " << data << "\n";
    printStack(queue);
        
    return 0;
}
