#include <string>
#include "DataType.h"

using namespace std;

#ifndef VOID_H
#define VOID_H
class Environment;

class Void : public DataType {
public:
    Void();
    Void(const Void& orig);
    virtual ~Void();
    virtual DataType* eval(Environment& e);
    virtual void print();

    int dataType() {
        return TYPE_VOID;
    }

    virtual string toString() {
        return "";
    }
private:

};

#endif /* VOID_H */

