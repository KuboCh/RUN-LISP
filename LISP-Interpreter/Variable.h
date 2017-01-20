#ifndef VARIABLE_H
#define VARIABLE_H

#include "DataType.h"


class Variable : public DataType {
public:
    Variable();
    Variable(string name, DataType *value, bool constant);
    Variable(const Variable& orig);
    virtual ~Variable();
    void eval();
    virtual void print();
    virtual int dataType() { return TYPE_PARAMETR; }
    DataType *value;
    string name;
    bool constant;
    string toString() { return value->toString(); }
private:
    
};

#endif /* VARIABLE_H */

