#include "Function.h"
#include "DataType.h"
#include "Environment.h"
#include "Parameter.h"
#include "LispStack.h"
#include "Nil.h"
#include "Number.h"
#include "Error.h"
#include "Memory.h"

Function::Function() {
    functionEnvironment = new Environment();
}

Function::Function(Environment* e) {
    functionEnvironment = e;
}

Function::Function(const Function& orig) {
}

Function::~Function() {
}

Function::Function(const string& name) {
    this->name = name;
}

void Function::addArgument(string name) {
    argsNames.push_back(name);
}

void Function::addToBody(pair<Function*, list<Parameter*> > ribf) {
    body.push_back(ribf);
}

DataType* Function::eval(Environment *e) {
    LispStack::getInstance().push(this); // vlozi sa na stack
    cout << "Pushing " + this->name << endl;
    DataType* result = new Nil();
    // Ak ma funkcia body functions, treba ich vsetky vyhodnotit v jej environmente
    for (list<pair<Function*, list<Parameter*> > >::iterator it = body.begin(); it != body.end(); ++it) {
        result = evalFunctionInBody(it);
        if (result->dataType() == DataType::TYPE_ERROR) {
            break; // return that error
        }
        if (result->isResult) {
            break;
        }
    }
    cout << "Poping " + this->name + " value is " << result->toString() << endl;
    LispStack::getInstance().pop(); // vyberie sa zo stacku
    return result;
}

bool Function::checkArgCount(int givenArgCount) {
    return givenArgCount == argsNames.size();
}

DataType* Function::evalFunctionInBody(list<pair<Function*, list<Parameter*> > >::iterator functionData) {
    if (!((*functionData).first->checkArgCount((*functionData).second.size()))) {
        return new Error("Wrong number of arguments of " + (*functionData).first->name);
    }
    cout << "Evaluating function " << (*functionData).first->name << endl;
    //eval of if
    if ((*functionData).first->name == "if") {
        list<Parameter*>::iterator paramOfIf = (*functionData).second.begin();
        if ((*paramOfIf)->eval(functionEnvironment)->eval(functionEnvironment)->dataType() == DataType::TYPE_TRUE) {
            paramOfIf++;
        } else {
            paramOfIf++;
            paramOfIf++;
        }
        return (*paramOfIf)->eval(functionEnvironment)->eval(functionEnvironment);
    }

    //eval of for
    if ((*functionData).first->name == "for") {
        return evalForCycle(functionData);
    }
    if ((*functionData).first->name == "return") {
        DataType* result = (*(*functionData).second.begin())->eval(functionEnvironment)->eval(functionEnvironment);
        result->isResult = true;
        return result;
    }
    LispStack::getInstance().push((*functionData).first);
    cout << "pushing " << (*functionData).first->name << endl;
    (*functionData).first->functionEnvironment = Memory::getInstance().get();
    Environment *environment = (*functionData).first->functionEnvironment; //new Environment();
    int argPos = 0;
    for (list<Parameter*>::iterator paramIt = (*functionData).second.begin(); paramIt != (*functionData).second.end(); ++paramIt) {
        try {
            DataType *par = (*paramIt)->eval(functionEnvironment)->eval(functionEnvironment);
            if (par->dataType() == DataType::TYPE_ERROR) {
                return par;
            }
            environment->addVariable((*functionData).first->getParameterNameAt(argPos), par, false);
        } catch (const char* error) {
            return new Error(error);
        }
        argPos++;
    }
    LispStack::getInstance().pop();
    //    cout << "--------------------------------------" << endl;
    //    environment->print();
    //    cout << "--------------------------------------" << endl;
    return (*functionData).first->eval(environment);
}

string Function::getParameterNameAt(int position) {
    if (position >= argsNames.size()) {
        throw "Trying to get parameter on position that doesn't exist.";
    }
    return argsNames.at(position);
}

DataType* Function::evalForCycle(list<pair<Function*, list<Parameter*> > >::iterator functionData) {
    list<Parameter*>::iterator paramOfFor = (*functionData).second.begin();
    string itName = (*paramOfFor)->parameterName;
    paramOfFor++;
    DataType* fromDataType = (*paramOfFor)->eval(functionEnvironment);
    if (fromDataType->dataType() != DataType::TYPE_NUMBER) {
        return new Error("Loop bounds should be of type number.");
    }
    paramOfFor++;
    DataType* toDataType = (*paramOfFor)->eval(functionEnvironment);
    if (toDataType->dataType() != DataType::TYPE_NUMBER) {
        return new Error("Loop bounds should be of type number.");
    }
    functionEnvironment->addVariable(itName, fromDataType, false);
    int from = ((Number*) fromDataType)->value;
    int to = ((Number*) toDataType)->value;
    DataType* result = new Nil();
    paramOfFor++;
    for (int i = from; i < to; ++i) {
        for (list<Parameter*>::iterator it = paramOfFor; it != (*functionData).second.end(); ++it) {
            result = (*it)->eval(functionEnvironment)->eval(functionEnvironment);
            if (result->dataType() == DataType::TYPE_ERROR) {
                return result;
            }
            if (result->isResult){
                return result;
            }
        }
    }
    return result;
}