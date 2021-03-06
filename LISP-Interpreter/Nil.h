#include <string>
#include <iostream>
#include "Symbol.h"

using namespace std;

#ifndef NIL_H
#define NIL_H
class DataType;
class Environment;

class Nil : public Symbol {
public:
    Nil();
    Nil(const Nil& orig);
    virtual ~Nil();
    virtual DataType* eval(Environment* e);
    virtual void print();

    int dataType() {
        return TYPE_NIL;
    }

    string toString() {
        return "nil";
    }
private:

};

#endif /* NIL_H */

