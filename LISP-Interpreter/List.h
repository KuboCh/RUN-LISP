#include <list>

#include "DataType.h"

#ifndef LIST_H
#define LIST_H

using namespace std;

class List : public DataType {
public:
    List();
    List(const List& orig);
    virtual ~List();
    void eval();
    virtual void print();
    void addElement(DataType *element);
    int dataType() { return TYPE_LIST; }
    virtual string toString();
private:
    list<DataType*> elements;
};

#endif /* LIST_H */

