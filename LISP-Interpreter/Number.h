#include <string>
#include <iostream>
#include <stdlib.h>
#include "DataType.h"

using namespace std;

#ifndef NUMBER_H
#define NUMBER_H
class Environment;

class Number : public DataType {
public:
    Number();
    Number(int val);
    Number(const Number& orig);
    virtual ~Number();
    virtual DataType* eval(Environment& e);
    virtual void print();
    virtual string toString();

    virtual int dataType() {
        return TYPE_NUMBER;
    }
    
    int value;
private:
};

#endif /* NUMBER_H */

