#include "BuildInFunctions.h"
#include "Error.h"
#include "Void.h"
#include "LispStack.h"
#include "True.h"

BuildInPlus::BuildInPlus() {
    name = "+";
}

BuildInPlus::~BuildInPlus() {
}

DataType* BuildInPlus::sumNubers(Enviroment *e) {
    int sum = 0;
    for (int i = 0; i < e->getNumberOfVariables(); i++) {
        Variable *parametr = e->getVariable(Enviroment::varNameAt(i));
        if (parametr->value->dataType() == DataType::TYPE_NUMBER) {
            sum += ((Number*) parametr->value)->value;
        } else {
            return sumStrings(e);
        }
    }
    return new Number(sum);
}

DataType* BuildInPlus::sumStrings(Enviroment *e) {
    string sum = "";
    for (int i = 0; i < e->getNumberOfVariables(); i++) {
        Variable *parametr = e->getVariable(Enviroment::varNameAt(i));
        sum += parametr->value->toString();
    }
    return new String(sum);
}

bool BuildInPlus::checkArgCount(int givenArgCount) {
    return givenArgCount > 1;
}

DataType* BuildInPlus::eval(Enviroment *e) {
    if (e->getNumberOfVariables() < 2) {
        return new Error("Wrong number of arguments of +");
    }
    Variable *parametr = e->getVariable(Enviroment::varNameAt(0));
    if (parametr->value->dataType() == DataType::TYPE_NUMBER) {
        return sumNubers(e);
    }
    return sumStrings(e);
}

BuildInDefvar::BuildInDefvar() {
    name = "defvar";
}


DataType* BuildInDefvar::eval(Enviroment *e) {
    if (e->getNumberOfVariables() != 2) {
        return new Error("Wrong number of arguments of defvar, requered 2");
    }
    //definuje premenn v enviromente funkcie z ktorej bola volana
    Function *parentFunction = LispStack::getInstance().pop();
    if (parentFunction != NULL) {
        parentFunction->functionEnviroment->addVariable(((String*) e->getVariable(Enviroment::varNameAt(0)))->value, e->getVariable(Enviroment::varNameAt(1))->value, false);
    }
    return new Void();
}

bool BuildInDefvar::checkArgCount(int givenArgCount) {
    return givenArgCount == 2;
}

BuildInMinus::BuildInMinus() {
    name = "-";
}

bool BuildInMinus::checkArgCount(int givenArgCount){
    return givenArgCount > 0;
}

DataType* BuildInMinus::eval(Enviroment* e) {
    Variable *parametr = e->getVariable(Enviroment::varNameAt(0));
        if (parametr->value->dataType() != DataType::TYPE_NUMBER) {
            return new Error("Parametr of minus (-) must be number");
        }
    if (e->getNumberOfVariables() == 1) {
        return new Number(0 - ((Number*) parametr->value)->value);
    }
    int sum = ((Number*) parametr->value)->value;
    for (int i = 1; i < e->getNumberOfVariables(); i++) {
        Variable *parametr = e->getVariable(Enviroment::varNameAt(i));
        if (parametr->value->dataType() == DataType::TYPE_NUMBER) {
            sum -= ((Number*) parametr->value)->value;
        } else {
            return new Error("Parametr of minus (-) must be number");
        }
    }
    return new Number(sum);
}

BuildInMultiplication::BuildInMultiplication() {
    name = "*";
}

bool BuildInMultiplication::checkArgCount(int givenArgCount) {
    return givenArgCount > 1;
}

DataType* BuildInMultiplication::eval(Enviroment* e) {
    int sum = 0;
    for (int i = 0; i < e->getNumberOfVariables(); i++) {
        Variable *parametr = e->getVariable(Enviroment::varNameAt(i));
        if (parametr->value->dataType() == DataType::TYPE_NUMBER) {
            if (i == 0) {
                sum = ((Number*) parametr->value)->value;
            } else {
                sum *= ((Number*) parametr->value)->value;
            }
        } else {
            return new Error("Parametr of multiplication (*) must be number");
        }
    }
    return new Number(sum);
}

BuildInDefconst::BuildInDefconst() {
    name = "defconst";
}

bool BuildInDefconst::checkArgCount(int givenArgCount) {
    return givenArgCount == 2;
}

DataType* BuildInDefconst::eval(Enviroment *e) {
    if (checkArgCount(e->getNumberOfVariables())) {
        return new Error("Wrong number of arguments of defconst, requered 2");
    }
    //definuje premenn v enviromente funkcie z ktorej bola volana
    Function *parentFunction = LispStack::getInstance().pop();
    if (parentFunction != NULL) {
        parentFunction->functionEnviroment->addVariable(((String*) e->getVariable(Enviroment::varNameAt(0)))->value, e->getVariable(Enviroment::varNameAt(1))->value, true);
    }
    return new Void();
}

BuildInList::BuildInList() {
    name = "list";
}

bool BuildInList::checkArgCount(int givenArgCount){
    return true;
}

DataType* BuildInList::eval(Enviroment* e) {
    List *list = new List();
    for (int i = 0; i < e->getNumberOfVariables(); i++){
        list->addElement(e->getVariable(Enviroment::varNameAt(i)));
    }
    return list;
}





