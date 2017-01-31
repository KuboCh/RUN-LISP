#include "Parameter.h"
#include "Error.h"
#include "String.h"
#include "LispStack.h"
#include "Number.h"
#include "Variable.h"
#include "Environment.h"
#include "Function.h"
#include "Memory.h"

using namespace std;

Parameter::Parameter() {
}

Parameter::Parameter(const Parameter& orig) {
}

Parameter::Parameter(Array* value) {
    this->value = value;
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
            while (!tmpStack.empty()) { // return all popped functions back on stack
                LispStack::getInstance().push(tmpStack.top());
                tmpStack.pop();
            }
            if (v == NULL) {
                return new Error("Variable " + parameterName + " not declared");
            }
        }
        cout << "Parameter " << parameterName << " is " << v->value->toString() << endl;
        return v->value;
    }
    if (value != NULL) {
        if (value->isAtom()) {
//            if (((DataType*) value)->dataType() == DataType::TYPE_STRING) {
//                String *s = ((String*) value); 
//            } else
                return value->eval(e);
        }
        return value->eval(e);
    }
   
//    cout << "Parameter value is result of function " << function->name << endl;
//    return function->eval(*e);
    if (!(function->checkArgCount(parametersOfFunction.size()))) {
        return new Error("Wrong number of arguments of " + function->name);
    }
    cout << "Evaluating function " << function->name << endl;
    Environment *environment = Memory::getInstance().get();//new Environment();//
    int argPos = 0;
    for (list<Parameter*>::iterator paramIt = parametersOfFunction.begin(); paramIt != parametersOfFunction.end(); ++paramIt) {
        try {
            DataType *par = (*paramIt)->eval(e)->eval(e);
            if (par->dataType() == DataType::TYPE_ERROR) {
                return par;
            }
            environment->addVariable(function->getParameterNameAt(argPos), par, false);
        } catch (const char* error) {
            return new Error(error);
        }
        argPos++;
    }
    //    cout << "--------------------------------------" << endl;
    //    environment->print();
    //    cout << "--------------------------------------" << endl;
    function->functionEnvironment = environment;
    return function->eval(environment);
    
    
}