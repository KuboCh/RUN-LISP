#include <string>
#include <iostream>
#include "DataType.h"

using namespace std;

#ifndef STRING_H
#define STRING_H
class Environment;

class String : public DataType {
public:
    String();
    String(string s);
    String(const String& orig);
    virtual ~String();
    virtual DataType* eval(Environment* e);
    virtual void print();

    virtual int dataType() {
        return TYPE_STRING;
    }

    string toString() {
        return value;
    }

    string value;

private:

};

#endif /* STRING_H */

