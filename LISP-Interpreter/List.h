#include <list>
#include "DataType.h"

using namespace std;

#ifndef LIST_H
#define LIST_H
class Enviroment;

class List : public DataType {
public:
    List();
    List(const List& orig);
    virtual ~List();
     virtual DataType* eval(Enviroment& e);
    virtual void print();
    void addElement(DataType *element);
    int dataType() { return TYPE_LIST; }
    virtual string toString();
private:
    list<DataType*> elements;
};

#endif /* LIST_H */

