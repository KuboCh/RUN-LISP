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

    if (function != NULL) {
        //    cout << "Parameter value is result of function " << function->name << endl;
        //    return function->eval(*e);
        if (!(function->checkArgCount(parametersOfFunction.size()))) {
            return new Error("Wrong number of arguments of " + function->name);
        }
        cout << "Evaluating function " << function->name << endl;
        if (function->name == "if") {
            list<Parameter*>::iterator paramOfIf = parametersOfFunction.begin();
            if ((*paramOfIf)->eval(e)->eval(e)->dataType() == DataType::TYPE_TRUE) {
                paramOfIf++;
            } else {
                paramOfIf++;
                paramOfIf++;
            }
            return (*paramOfIf)->eval(e)->eval(e);
        }
        if (function->name == "for") {
            list<Parameter*>::iterator paramOfFor = parametersOfFunction.begin();
            string itName = (*paramOfFor)->parameterName;
            paramOfFor++;
            DataType* fromDataType = (*paramOfFor)->eval(e);
            if (fromDataType->dataType() != DataType::TYPE_NUMBER) {
                return new Error("Loop bounds should be of type number.");
            }
            paramOfFor++;
            DataType* toDataType = (*paramOfFor)->eval(e);
            if (toDataType->dataType() != DataType::TYPE_NUMBER) {
                return new Error("Loop bounds should be of type number.");
            }
            e->addVariable(itName, fromDataType, false);
            int from = ((Number*) fromDataType)->value;
            int to = ((Number*) toDataType)->value;
            DataType* result = NULL;
            paramOfFor++;
            for (int i = from; i < to; ++i) {
                for (list<Parameter*>::iterator it = paramOfFor; it != parametersOfFunction.end(); ++it) {
                    result = (*it)->eval(e)->eval(e);
                    if (result->dataType() == DataType::TYPE_ERROR) {
                        return result;
                    }
                }
            }
            return result;
        }
        if (function->name == "return") {
            DataType* result = (*parametersOfFunction.begin())->eval(e)->eval(e);
            result->isResult = true;
            return result;
        }
        LispStack::getInstance().push(function);
        cout << "pushing " << function->name << endl;
        Environment *environment = Memory::getInstance().get(); //new Environment();//
        function->functionEnvironment = environment;
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
        LispStack::getInstance().pop();
        return function->eval(environment);
    }

    if (value != NULL) {
        return value->eval(e);
    }
}