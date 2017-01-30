#include <string>
#include <iostream>
#include "Symbol.h"

using namespace std;

#ifndef TRUE_H
#define TRUE_H
class DataType;
class Environment;

class True : public Symbol {
public:
    True();
    True(const True& orig);
    virtual ~True();
    virtual DataType* eval(Environment& e);
    virtual void print();

    virtual int dataType() {
        return TYPE_TRUE;
    }

    string toString() {
        return "true";
    }
    //    bool operator==(const True t){
    //        return true;
    //    }
    //    bool operator==(const False f){
    //        return false;
    //    }
private:

};

#endif /* TRUE_H */

