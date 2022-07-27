//
//  main.cpp
//  SinglyCircularLinkedList
//
//  Created by lZackx on 2022/7/27.
//

#include <iostream>
#include "SinglyCircularLinkedList.hpp"


void printList(SinglyCircularLinkedList *list) {
    std::cout << "count:" << list->length << "\n[";
    list->traverseNode([&](int index, struct Node *node) {
        std::cout << node->data;
        if (index < (list->length - 1)) {
            std::cout << ", ";
        }
    });
    std::cout << "]\n";
}


int main(int argc, const char * argv[]) {
    
    SinglyCircularLinkedList *list = new SinglyCircularLinkedList();
    // add
    for (int i = 0; i < 10; i++) {
        struct Node *node = list->createNode(i);
        list->addNode(node);
    }
    printList(list);
    
    // insert
    struct Node *insertNode = list->createNode(-1);
    list->insertNode(10, insertNode);
    printList(list);
    
    // delete
    list->deleteNode(0);
    printList(list);
    
    // clear
    list->clearNodes();
    printList(list);
    
    return 0;
}
