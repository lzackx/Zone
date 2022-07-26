//
//  main.cpp
//  LinearList
//
//  Created by lZackx on 2022/7/26.
//

#include <iostream>
#include "LinearList.hpp"


void printList(LinearList *list) {
    std::cout << "count:" << list->length << "\n[";
    list->traverseData([&](int index, int data) {
        std::cout << data;
        if (index < (list->length - 1)) {
            std::cout << ", ";
        }
    });
    std::cout << "]\n";
}

int main(int argc, const char * argv[]) {
    
    LinearList *list = new LinearList(10);
    printList(list);
    
    // add
    for (int i = 0; i < 9; i++) {
        list->addData(i);
    }
    printList(list);
    
    // insert
    list->insertData(5, -1);
    printList(list);
    
    // delete
    list->deleteData(8);
    printList(list);
    
    // clear
    list->clearData();
    printList(list);
    
    return 0;
}
