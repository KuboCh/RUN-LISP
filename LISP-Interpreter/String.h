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
    friend ostream& operator<<(ostream& out, const String& s) {
        out << s.value << endl;
        return out;
    }
    string value;
private:

};

#endif /* STRING_H */

