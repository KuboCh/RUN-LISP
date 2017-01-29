#include <string>
#include "DataType.h"

using namespace std;

#ifndef SYMBOL_H
#define SYMBOL_H
class Enviroment;

class Symbol : public DataType {
public:
    Symbol();
    Symbol(const string& s);
    Symbol(const Symbol& orig);
    virtual ~Symbol();

    virtual DataType* eval(Enviroment& e);

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
