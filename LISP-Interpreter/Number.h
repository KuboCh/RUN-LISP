#include <string>
#include <iostream>
#include <stdlib.h>
#include "DataType.h"

using namespace std;

#ifndef NUMBER_H
#define NUMBER_H
class Enviroment;

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

