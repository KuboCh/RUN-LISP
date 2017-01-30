#include "Environment.h"
#include "Variable.h"
#include "Error.h"
#include "Function.h"

Environment::Environment() {
    numberOfVariables = 0;
}

Environment::Environment(const Environment& orig) {
}

Environment::~Environment() {
}

Variable* Environment::getVariable(string name) {
    if (variables.find(name) == variables.end())
        return NULL;
    return variables[name];
}

DataType* Environment::addVariable(string name, DataType *value, bool isConstant) {
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

map<string, Variable*>::const_iterator Environment::getParametersIterator() {
    return variables.begin();
}

map<string, Variable*>::const_iterator Environment::getParametersIteratorEnd() {
    return variables.end();
}

/*
 * Add the given function into environment. Also includes check whether the function 
 * is in this environment.
 */
Function* Environment::addFunction(Function* function) {
    if (this->getFunction(function->name))
        throw "Function " + function->name + " is already defined.";
    functions.push_back(function);
    return function;
}

Function* Environment::getFunction(string name) {
    for (vector<Function*>::iterator it = functions.begin(); it != functions.end(); it++) {
        if ((*it)->name == name) {
            return (*it);
        }
    }
    return NULL;
}

int Environment::getNumberOfVariables() {
    return numberOfVariables;
}

void Environment::print() {
    cout << "Variables:" << endl;
    for (map<string, Variable*>::iterator it = variables.begin(); it != variables.end(); ++it) {
        cout << (*it).first << " = " << (*it).second->toString() << endl;
    }
    cout << "Functions:" << endl;
    for (vector<Function*>::iterator it = functions.begin(); it != functions.end(); ++it) {
        cout << (*it)->name << endl;
    }
}