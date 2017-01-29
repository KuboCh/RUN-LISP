#include <string>
#include "DataType.h"

#ifndef VOID_H
#define VOID_H

class Void : public DataType {
public:
     virtual DataType* eval(Enviroment& e);
    virtual void print();
    int dataType() { return TYPE_VOID; }
    virtual string toString() { return ""; }
    Void();
    Void(const Void& orig);
    virtual ~Void();
private:

};

#endif /* VOID_H */

