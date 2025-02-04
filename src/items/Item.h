#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
using namespace std;

class Item {
public:
    string name;
    int value;

    Item(const string &name, int value);
    
    virtual ~Item();
    virtual void use();
};

#endif
