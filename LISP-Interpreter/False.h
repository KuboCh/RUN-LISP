#include <string>
#include <iostream>
#include "Symbol.h"

using namespace std;

#ifndef FALSE_H
#define FALSE_H
class DataType;
class Enviroment;

class False : public Symbol {
public:
    False();
    False(const False& orig);
    virtual ~False();

    virtual DataType* eval(Enviroment& e);
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

