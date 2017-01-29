#include <string>
#include <iostream>
#include "DataType.h"
#include <stdlib.h>

#ifndef NUMBER_H
#define NUMBER_H

using namespace std;

class Number : public DataType {
public:
    Number();
    Number(int val);
    Number(const Number& orig);
    virtual ~Number();
    
     virtual DataType* eval(Enviroment& e);
    virtual void print();
    int value;
    virtual int dataType() { return TYPE_NUMBER; }
    virtual string toString(); 
private:
};

#endif /* NUMBER_H */

