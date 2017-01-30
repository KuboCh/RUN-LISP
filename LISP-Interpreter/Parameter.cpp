#include "Parameter.h"
#include "Error.h"
#include "String.h"
#include "LispStack.h"
#include "Number.h"
#include "Variable.h"
#include "Environment.h"
#include "Function.h"

using namespace std;

Parameter::Parameter() {
}

Parameter::Parameter(const Parameter& orig) {
}

Parameter::~Parameter() {
}

DataType* Parameter::eval(Environment *e) {
    if (parameterName != "") { // we have name, search for value in environments
        Variable *v = e->getVariable(parameterName);
        if (v == NULL) {
            stack<Function*> tmpStack;
            while (v == NULL && !LispStack::getInstance().isEmpty()) {
                Function *f = LispStack::getInstance().pop();
                tmpStack.push(f);
                v = f->functionEnvironment->getVariable(parameterName);
            }
            if (v == NULL) {
                return new Error("Variable " + parameterName + " not declared");
            }
            while (!tmpStack.empty()) { // return all popped functions back on stack
                LispStack::getInstance().push(tmpStack.top());
                tmpStack.pop();
            }
        }
        cout << "Parameter " << parameterName << " is " << v->value->toString() << endl;
        return v->value;
    }
    if (value != NULL) {
        if (value->isAtom()) {
            if (((DataType*) value)->dataType() == DataType::TYPE_STRING) {
                String *s = ((String*) value); 
            } else
                return value->eval(*e);
        }
        return value->eval(*e);
    }
//    cout << "Parameter value is result of function " << function->name << endl;
//    return function->eval(*e);
}