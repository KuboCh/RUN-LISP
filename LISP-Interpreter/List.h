#include <list>
#include "DataType.h"

using namespace std;

#ifndef LIST_H
#define LIST_H
class Environment;

class List : public DataType {
public:
    List();
    List(const List& orig);
    virtual ~List();
    virtual DataType* eval(Environment* e);
    virtual void print();
    void addElement(DataType *element);
    virtual string toString();

    int dataType() {
        return TYPE_LIST;
    }
private:
    list<DataType*> elements;
};

#endif /* LIST_H */

