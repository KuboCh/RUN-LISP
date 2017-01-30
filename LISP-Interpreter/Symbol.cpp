#include "Symbol.h"
#include "Variable.h"
#include "Error.h"
#include "Environment.h"

Symbol::Symbol() {
}

Symbol::Symbol(const Symbol& orig) {
}

Symbol::~Symbol() {
}

Symbol::Symbol(const string& s) {
    value = s;
}

DataType* Symbol::eval(Environment& e) {
    Variable *var = e.getVariable(value);
    if (var == NULL) {
        Function * func = e.getFunction(value);
        if(func == NULL){
           return new Error("Symbol " + value + " not found in environment.");
        } else {
            return (DataType*) func;
        }
    } else {
        return (DataType*) var;
    }
}
