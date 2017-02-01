#include <string>
#include <iostream>
#include "Symbol.h"

using namespace std;

#ifndef FALSE_H
#define FALSE_H
class DataType;
class Environment;

class False : public Symbol {
public:
    False();
    False(const False& orig);
    virtual ~False();

    virtual DataType* eval(Environment* e);
    virtual void print();

    int dataType() {
        return TYPE_FALSE;
    }

    string toString() {
        return "false";
    }
private:

};

#endif /* FALSE_H */

