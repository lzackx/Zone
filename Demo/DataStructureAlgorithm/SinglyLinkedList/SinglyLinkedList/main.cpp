//
//  main.cpp
//  SinglyLinkedList
//
//  Created by lZackx on 2022/7/26.
//

#include <iostream>
#include "SinglyLinkedList.hpp"

void printList(SinglyLinkedList *list) {
    std::cout << "count:" << list->length() << "\n[";
    list->traverseNode([](struct Node * node) {
        std::cout << node->data;
        if (node->next) {
            std::cout << ", ";
        }
    });
    std::cout << "]\n";
}

int main(int argc, const char * argv[]) {
    
    SinglyLinkedList *list = new SinglyLinkedList();
    // add
    for (int i = 0; i < 10; i++) {
        struct Node *node = list->createNode(i);
        list->addNode(node);
    }
    printList(list);
    
    // insert
    struct Node *insertNode = list->createNode(-1);
    list->insertNode(insertNode, 0);
    printList(list);
    
    // delete
    list->deleteNode(8);
    printList(list);
    
    // clear
    list->clearNode();
    printList(list);
    
    return 0;
}
