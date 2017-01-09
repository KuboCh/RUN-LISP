#include <string>
#include <iostream>
#include "DataType.h"

#ifndef FALSE_H
#define FALSE_H

using namespace std;

class False : public DataType {
public:
    False();
    False(const False& orig);
    virtual ~False();
    
    void eval();
    virtual void print();
private:

};

#endif /* FALSE_H */

