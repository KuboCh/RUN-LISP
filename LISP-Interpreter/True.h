#include <string>
#include <iostream>
#include "Symbol.h"

using namespace std;

#ifndef TRUE_H
#define TRUE_H
class DataType;
class Enviroment;

class True : public Symbol {
public:
    True();
    True(const True& orig);
    virtual ~True();
    
     virtual DataType* eval(Enviroment& e);
    virtual void print();
    virtual int dataType() { return TYPE_TRUE; }
    string toString() { return "true"; }
private:

};

#endif /* TRUE_H */

