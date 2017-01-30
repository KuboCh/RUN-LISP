#include <string>
#include "DataType.h"

using namespace std;

#ifndef VARIABLE_H
#define VARIABLE_H

class Variable : public DataType {
public:
    Variable();
    Variable(string name, DataType *value, bool constant);
    Variable(const Variable& orig);
    virtual ~Variable();
    virtual DataType* eval(Environment& e);
    virtual void print();

    virtual int dataType() {
        return TYPE_PARAMETER;
    }

    string toString() {
        return value->toString();
    }

    DataType *value;
    string name;
    bool constant;
private:

};

#endif /* VARIABLE_H */

