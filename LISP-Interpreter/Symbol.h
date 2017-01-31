#include <string>
#include "DataType.h"

using namespace std;

#ifndef SYMBOL_H
#define SYMBOL_H
class Environment;

class Symbol : public DataType {
public:
    Symbol();
    Symbol(const string& s);
    Symbol(const Symbol& orig);
    virtual ~Symbol();
    virtual DataType* eval(Environment* e);

    virtual void print() {
        cout << value << endl;
    }

    virtual int dataType() {
        return TYPE_SYMBOL;
    }

    virtual string toString() {
        return value;
    }
    
    string value;
private:

};

#endif /* SYMBOL_H */

