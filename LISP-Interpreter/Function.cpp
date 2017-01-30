#include "Function.h"
#include "DataType.h"
#include "Environment.h"
#include "Parameter.h"
#include "LispStack.h"
#include "Nil.h"
#include "Number.h"
#include "Error.h"

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

DataType* Function::eval(Environment &e) {
    *functionEnvironment = e;
    LispStack::getInstance().push(this); // vlozi sa na stack
    cout << "Pushing " + this->name << endl;
    DataType* result = new Nil();
    // Ak ma funkcia body functions, treba ich vsetky vyhodnotit v jej environmente
    for (list<pair<Function*, list<Parameter*> > >::iterator it = body.begin(); it != body.end(); ++it) {
        result = evalFunctionInBody(it);
        if (result->dataType() == DataType::TYPE_ERROR) {
            return result; // return that error
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
    Environment *environment = new Environment();
    int argPos = 0;
    for (list<Parameter*>::iterator paramIt = (*functionData).second.begin(); paramIt != (*functionData).second.end(); ++paramIt) {
        try {
            environment->addVariable((*functionData).first->getParameterNameAt(argPos), (*paramIt)->eval(functionEnvironment)->eval(*functionEnvironment), false);
        } catch (const char* error) {
            return new Error(error);
        }
        argPos++;
    }
    //    cout << "--------------------------------------" << endl;
    //    environment->print();
    //    cout << "--------------------------------------" << endl;
    return (*functionData).first->eval(*environment);
}

string Function::getParameterNameAt(int position) {
    if (position >= argsNames.size()) {
        throw "Trying to get parameter on position that doesn't exist.";
    }
    return argsNames.at(position);
}