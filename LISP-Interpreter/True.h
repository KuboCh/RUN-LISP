#include <string>
#include <iostream>
#include "DataType.h"
#include "Symbol.h"

#ifndef TRUE_H
#define TRUE_H

using namespace std;

class True : public Symbol {
public:
    True();
    True(const True& orig);
    virtual ~True();
    
    void eval();
    virtual void print();
    virtual int dataType() { return TYPE_TRUE; }
    string toString() { return "true"; }
private:

};

#endif /* TRUE_H */

