//
//  main.cpp
//  LinearQueue
//
//  Created by lZackx on 2022/8/30.
//

#include <iostream>
#include "LinearQueue.hpp"


void printQueue(LinearQueue *list) {
    std::cout << "length:" << list->length() << "\n[";
    list->traverse([&](int index, int data) {
        std::cout << data;
        std::cout << ", ";
    });
    std::cout << "]\n";
}

int main(int argc, const char * argv[]) {
    
    LinearQueue *queue = new LinearQueue(10);
    printQueue(queue);

    // enqueue
    for (int i = 0; i < queue->capacity; i++) {
        queue->enqueue(i);
    }
    printQueue(queue);


    // dequeue
    int data = queue->dequeue();
    std::cout << "dequeue: " << data << "\n";
    printQueue(queue);
    
    data = queue->dequeue();
    std::cout << "dequeue: " << data << "\n";
    printQueue(queue);
    
    // 
    queue->enqueue(11);
    printQueue(queue);
    
    data = queue->dequeue();
    std::cout << "dequeue: " << data << "\n";
    printQueue(queue);
    
    return 0;
}
