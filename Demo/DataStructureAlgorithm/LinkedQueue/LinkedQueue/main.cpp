//
//  main.cpp
//  LinkedQueue
//
//  Created by lZackx on 2022/8/30.
//

#include <iostream>
#include "LinkedQueue.hpp"


void printQueue(LinkedQueue *list) {
    std::cout << "length:" << list->length() << "\n[";
    list->traverse([&](Node *node) {
        std::cout << node->data;
        std::cout << ", ";
    });
    std::cout << "]\n";
}

int main(int argc, const char * argv[]) {
    
    LinkedQueue *queue = new LinkedQueue();
    printQueue(queue);

    // enqueue
    for (int i = 0; i < 10; i++) {
        struct Node *node = queue->createNode(i);
        queue->enqueue(node);
    }
    printQueue(queue);


    // dequeue
    struct Node *dequeueNode = queue->dequeue();
    std::cout << "dequeue: " << dequeueNode->data << "\n";
    printQueue(queue);
    
    dequeueNode = queue->dequeue();
    std::cout << "dequeue: " << dequeueNode->data << "\n";
    printQueue(queue);
    
    //
    struct Node *newNode = queue->createNode(11);
    queue->enqueue(newNode);
    printQueue(queue);
    
    dequeueNode = queue->dequeue();
    std::cout << "dequeue: " << dequeueNode->data << "\n";
    printQueue(queue);
    
    return 0;
}
