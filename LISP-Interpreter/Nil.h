#include <string>
#include <iostream>
#include "DataType.h"
#include "Symbol.h"

#ifndef NIL_H
#define NIL_H

using namespace std;

class Nil : public Symbol  {
public:
    Nil();
    Nil(const Nil& orig);
    virtual ~Nil();
    
     virtual DataType* eval(Enviroment& e);
    virtual void print();
    int dataType() { return TYPE_NIL; }
    string toString() { return "nil"; }
private:

};

#endif /* NIL_H */

