#include <string>
#include <iostream>
#include "DataType.h"

#ifndef STRING_H
#define STRING_H

using namespace std;

class String : public DataType {
public:
    String();
    String(string s);
    String(const String& orig);
    virtual ~String();
    
    void eval();
    virtual void print();
    virtual int dataType() { return TYPE_STRING; }
    string value;
    string toString() { return value; }
private:

};

#endif /* STRING_H */

