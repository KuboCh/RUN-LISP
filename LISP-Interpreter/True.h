#include <string>
#include <iostream>
#include "DataType.h"

#ifndef TRUE_H
#define TRUE_H

using namespace std;

class True : public DataType {
public:
    True();
    True(const True& orig);
    virtual ~True();
    
    void eval();
    virtual void print();
private:

};

#endif /* TRUE_H */

