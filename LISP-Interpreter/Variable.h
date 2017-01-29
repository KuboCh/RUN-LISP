#include <string>
#include "DataType.h"

using namespace std;

#ifndef VARIABLE_H
#define VARIABLE_H
//class DataType;

class Variable : public DataType {
public:
    Variable();
    Variable(string name, DataType *value, bool constant);
    Variable(const Variable& orig);
    virtual ~Variable();
    virtual DataType* eval(Enviroment& e);
    virtual void print();

    virtual int dataType() {
        return TYPE_PARAMETR;
    }
    DataType *value;
    string name;
    bool constant;

    string toString() {
        return value->toString();
    }
private:

};

#endif /* VARIABLE_H */

