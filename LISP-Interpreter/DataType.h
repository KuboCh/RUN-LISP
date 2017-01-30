#include <string>
#include <iostream>
#include "Array.h"

using namespace std;

#ifndef DATATYPE_H
#define DATATYPE_H

class DataType : public Array {
public:
    static const int TYPE_NUMBER = 0;
    static const int TYPE_STRING = 1;
    static const int TYPE_LIST = 2;
    static const int TYPE_FALSE = 3;
    static const int TYPE_TRUE = 4;
    static const int TYPE_NIL = 5;
    static const int TYPE_ERROR = 6;
    static const int TYPE_PARAMETER = 7;
    static const int TYPE_VOID = 8;
    static const int TYPE_SYMBOL = 9;
    static const int TYPE_FUNCTION = 10;

    DataType();
    DataType(const DataType& orig);
    virtual ~DataType();

    virtual DataType* eval(Environment& e);
    virtual void print();
    virtual int dataType();
    virtual string toString();
    string typeToString();
private:

};

#endif /* DATATYPE_H */

