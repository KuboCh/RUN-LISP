#include <string>
#include <iostream>
#include "DataType.h"
#include "Symbol.h"

#ifndef FALSE_H
#define FALSE_H

using namespace std;

class False : public Symbol {
public:
    False();
    False(const False& orig);
    virtual ~False();
    
    void eval();
    virtual void print();
    int dataType() { return TYPE_FALSE; }
    string toString() { return "false"; }
private:

};

#endif /* FALSE_H */

