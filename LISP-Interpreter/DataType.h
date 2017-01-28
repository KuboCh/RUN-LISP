#include <string>
#include <iostream>
#include "Array.h"

#ifndef DATATYPE_H
#define DATATYPE_H

using namespace std;

class DataType : public Array {
public:
    static const int TYPE_NUMBER = 0;
    static const int TYPE_STRING = 1;
    static const int TYPE_LIST = 2;
    static const int TYPE_FALSE = 3;
    static const int TYPE_TRUE = 4;
    static const int TYPE_NIL = 5;
    static const int TYPE_ERROR = 6;
    static const int TYPE_PARAMETR = 7;
    static const int TYPE_VOID = 8;
    static const int TYPE_SYMBOL = 9;

    DataType();
    DataType(const DataType& orig);
    virtual ~DataType();

    virtual void eval() {
        cout << "Abstract DataType eval() should be overriden." << endl;
    }

    virtual void print() {
        cout << "Abstract DataType print should be overriden." << endl;
    }

    virtual int dataType() {
        cout << "Abstract DataType type() should be overriden." << endl;
        return TYPE_ERROR;
    }

    virtual string toString() {
        cout << "Abstract DataType type() should be overriden." << endl;
        return "";
    }
private:

};

#endif /* DATATYPE_H */

