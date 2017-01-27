#include "Enviroment.h"
#include "Variable.h"
#include "Error.h"
#include "Function.h"

Enviroment::Enviroment() {
    numberOfVariables = 0;
}

Enviroment::Enviroment(const Enviroment& orig) {
}

Enviroment::~Enviroment() {
}

Variable* Enviroment::getVariable(string name) {
    if (variables.find(name) == variables.end())
        return NULL;
    return variables[name];
}

DataType* Enviroment::addVariable(string name, DataType *value, bool isConstant) {
    map<string, Variable*>::iterator it = variables.find(name);
    if (it != variables.end()) {
        if (it->second->constant) {
            return new Error("Can't change value of constant");
        }
        it->second->value = value;
        it->second->constant = isConstant;
        return it->second;
    }
    Variable *newVariable = new Variable(name, value, isConstant);
    variables[name] = newVariable;
    numberOfVariables++;
    return newVariable;
}

map<string, Variable*>::const_iterator Enviroment::getParametrsIterator() {
    return variables.begin();
}

map<string, Variable*>::const_iterator Enviroment::getParametrsIteratorEnd() {
    return variables.end();
}

Function* Enviroment::addFunction(Function* function) {
    //TODO kontrola ci uz take nahodou neexistuje
    functions.push_back(function);
    return function;
}

Function* Enviroment::getFunction(string name) {
    for (vector<Function*>::iterator it = functions.begin(); it != functions.end(); it++) {
        if ((*it)->name == name) {
            return (*it);
        }
    }
    return NULL;
}

int Enviroment::getNumberOfVariables() {
    return numberOfVariables;
}

void Enviroment::print() {
    cout << "Variables:" << endl;
    for (map<string, Variable*>::iterator it = variables.begin(); it != variables.end(); ++it) {
        cout << (*it).first << " = " << (*it).second->toString() << endl;
    }
    cout << "Functions:" << endl;
    for (vector<Function*>::iterator it = functions.begin(); it != functions.end(); ++it) {
        cout << (*it)->name << endl;
    }
}