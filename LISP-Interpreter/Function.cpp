#include "Function.h"
#include "DataType.h"
#include "Enviroment.h"
#include "Parametr.h"
#include "LispStack.h"
#include "Nil.h"
#include "Number.h"
#include "Error.h"

Function::Function() {
    argCount = 0;
    functionEnviroment = new Enviroment();
}

Function::Function(Enviroment* e) {
    functionEnviroment = e;
    argCount = 0;
}

Function::Function(const Function& orig) {
}

Function::~Function() {
}

void Function::addArgument(string name) {
    //args.push_back(Parametr(name, NULL, false));
    argsNames.push_back(name);
    argCount++;
}

void Function::addToBody(pair<Function*, list<Parametr*> > ribf) {//Function* function, list<Parametr*> parametrs) {
    body.push_back(ribf);
}

DataType* Function::eval(Enviroment* e) {
    functionEnviroment = e;
    LispStack::getInstance().push(this); // vlozi sa na stack
    cout << "Pushing " + this->name << endl;
    DataType* result = new Nil();
    // Ak ma funkcia body functions, treba ich vsetky vyhodnotit v jej environmente
    for (list<pair<Function*, list<Parametr*> > >::iterator it = body.begin(); it != body.end(); ++it) {
        result = evalFunctionInBody(it);
        if (result->dataType() == DataType::TYPE_ERROR) {
            return result; // return that error
        }
    }
    cout << "Poping " + this->name + " value is " << ((Number*) result)->value << endl;
    LispStack::getInstance().pop(); // vyberie sa zo stacku
    return result;
}

bool Function::checkArgCount(int givenArgCount) {
    return givenArgCount == argCount;
}

DataType* Function::evalFunctionInBody(list<pair<Function*, list<Parametr*> > >::iterator functionData) {
    if (!((*functionData).first->checkArgCount((*functionData).second.size()))) {
        return new Error("Wrong number of arguments of " + (*functionData).first->name);
    }
    cout << "Evaluating function " << (*functionData).first->name << endl;
    Enviroment *enviroment = new Enviroment();
    int argPos = 0;
    for (list<Parametr*>::iterator paramIt = (*functionData).second.begin(); paramIt != (*functionData).second.end(); ++paramIt) {
        try {
            enviroment->addVariable((*functionData).first->getParametrNameAt(argPos), (*paramIt)->eval(functionEnviroment), false);
        } catch (const char* error) {
            return new Error(error);
        }
        argPos++;
    }
//    cout << "--------------------------------------" << endl;
//    enviroment->print();
//    cout << "--------------------------------------" << endl;
    return (*functionData).first->eval(enviroment);
}

string Function::getParametrNameAt(int position) {
    if (position >= argsNames.size()) {
        throw "Trying to get parameter on position that doesn't exist."; //TODO
    }
    return argsNames.at(position);
}

void Function::printFunctionParams() {
    cout << this->name;
    for (list<pair<Function*, list<Parametr*> > >::iterator it = body.begin(); it != body.end(); ++it) {
        (*it).first->printFunctionParams();
        for (list<Parametr*>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2) {
            if ((*it2)->function != NULL) {
                (*it2)->function->printFunctionParams();
            }
        }
    }
}