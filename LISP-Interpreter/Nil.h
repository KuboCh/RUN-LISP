#include <string>
#include <iostream>
#include "DataType.h"

#ifndef NIL_H
#define NIL_H

using namespace std;

class Nil : public DataType {
public:
    Nil();
    Nil(const Nil& orig);
    virtual ~Nil();
    
    void eval();
    virtual void print();
    int dataType() { return TYPE_NIL; }
    string toString() { return "nil"; }
private:

};

#endif /* NIL_H */

