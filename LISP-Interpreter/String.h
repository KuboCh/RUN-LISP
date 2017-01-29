#include <string>
#include <iostream>
#include "DataType.h"

using namespace std;

#ifndef STRING_H
#define STRING_H
class Enviroment;

class String : public DataType {
public:
    String();
    String(string s);
    String(const String& orig);
    virtual ~String();
    
     virtual DataType* eval(Enviroment& e);
    virtual void print();
    virtual int dataType() { return TYPE_STRING; }
    string value;
    string toString() { return value; }
private:

};

#endif /* STRING_H */

