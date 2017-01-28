#include "DataType.h"
#include <string>
#include "DataType.h"

using namespace std;

#ifndef SYMBOL_H
#define SYMBOL_H

class Symbol : public DataType {
public:
    Symbol();

    Symbol(const string& s) {
        value = s;
    }
    Symbol(const Symbol& orig);
    virtual ~Symbol();

    virtual void eval() {
        cout << "Abstract Symbol eval() should be overriden." << endl;
    }

    virtual void print() {
        cout << value << endl;
    }
    string value;

    virtual int dataType() {
        return TYPE_SYMBOL;
    }

    virtual string toString() {
        return value;
    }
private:

};

#endif /* SYMBOL_H */

