//
//  LinearList.hpp
//  LinearList
//
//  Created by lZackx on 2022/7/26.
//

#ifndef LinearList_hpp
#define LinearList_hpp

#include <stdio.h>
#include <functional>

class LinearList {
public:
    int *data;
    int length;
    int maxLength;

    LinearList(int count);
    ~LinearList();
    
    bool empty();
    
    void addData(int data);
    void insertData(int index, int data);
    
    int getData(int index);
    
    void deleteData(int index);
    void clearData();
    
    void traverseData(std::function<void(int index, int data)> lambda);
};

#endif /* LinearList_hpp */
