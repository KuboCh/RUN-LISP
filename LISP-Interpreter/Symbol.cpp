#include "Symbol.h"

Symbol::Symbol() {
}

Symbol::Symbol(const Symbol& orig) {
}

Symbol::~Symbol() {
}

Symbol::Symbol(const string& s) {
    value = s;
}

DataType* Symbol::eval(Enviroment& e) {
    Variable *var = e.getVariable(value);
    if (var == NULL) {
        return new Error("Variable " + value + " not found");
    }
    return (DataType*) var;
}
