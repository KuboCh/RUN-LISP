#include <vector>
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
    void addElement(Array *element);
    virtual string toString();

    int dataType() {
        return TYPE_LIST;
    }
    vector<Array*> elements;
};

#endif /* LIST_H */

