#include <string>
#include <iostream>
#include "DataType.h"

#ifndef NUMBER_H
#define NUMBER_H

using namespace std;

class Number : public DataType {
public:
    Number();
    Number(int val);
    Number(const Number& orig);
    virtual ~Number();
    
    void eval();
    friend ostream& operator<<(ostream& out, const Number& number) {
        out << number.value << endl;
        return out;
    }
    int value;
private:
};

#endif /* NUMBER_H */

