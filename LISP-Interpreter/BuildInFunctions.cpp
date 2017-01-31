#include "BuildInFunctions.h"
#include "Variable.h"
#include "DataType.h"
#include "Environment.h"
#include "Function.h"
#include "List.h"
#include "Number.h"
#include "String.h"
#include "Error.h"
#include "LispStack.h"
#include "Void.h"
#include "False.h"
#include "True.h"

BuildInPlus::BuildInPlus() {
    name = "+";
}

BuildInPlus::~BuildInPlus() {
}

DataType* BuildInPlus::sumNubers(Environment *e) {
    int sum = 0;
    for (int i = 0; i < e->getNumberOfVariables(); i++) {
        Variable *parameter = e->getVariable(Environment::varNameAt(i));
        if (parameter->value->dataType() == DataType::TYPE_NUMBER) {
            sum += ((Number*) parameter->value)->value;
        } else {
            return sumStrings(e);
        }
    }
    return new Number(sum);
}

DataType* BuildInPlus::sumStrings(Environment *e) {
    string sum = "";
    for (int i = 0; i < e->getNumberOfVariables(); i++) {
        Variable *parameter = e->getVariable(Environment::varNameAt(i));
        sum += parameter->value->toString();
    }
    return new String(sum);
}

bool BuildInPlus::checkArgCount(int givenArgCount) {
    return givenArgCount > 1;
}

DataType* BuildInPlus::eval(Environment *e) {
    if (e->getNumberOfVariables() < 2) {
        return new Error("Wrong number of arguments of +");
    }
    Variable *parameter = e->getVariable(Environment::varNameAt(0));
    if (parameter->value->dataType() == DataType::TYPE_NUMBER) {
        return sumNubers(e);
    }
    return sumStrings(e);
}

string BuildInPlus::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

BuildInDefvar::BuildInDefvar() {
    name = "defvar";
}

DataType* BuildInDefvar::eval(Environment *e) {
    if (e->getNumberOfVariables() != 2) {
        return new Error("Wrong number of arguments of defvar, requered 2");
    }
    //definuje premenn v environmente funkcie z ktorej bola volana
    Function *parentFunction = LispStack::getInstance().pop();
    if (parentFunction != NULL) {
        //parentFunction->functionEnvironment->addVariable(((String*) e->getVariable(Environment::varNameAt(0)))->value, e->getVariable(Environment::varNameAt(1))->value, false);
        parentFunction->functionEnvironment->addVariable(((String*) e->getVariable(Environment::varNameAt(0))->value)->value,
                e->getVariable(Environment::varNameAt(1))->value, false);
    }
    return new Void();
}

string BuildInDefvar::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

bool BuildInDefvar::checkArgCount(int givenArgCount) {
    return givenArgCount == 2;
}

BuildInMinus::BuildInMinus() {
    name = "-";
}

bool BuildInMinus::checkArgCount(int givenArgCount) {
    return givenArgCount > 0;
}

string BuildInMinus::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

DataType* BuildInMinus::eval(Environment *e) {
    Variable *parameter = e->getVariable(Environment::varNameAt(0));
    if (parameter->value->dataType() != DataType::TYPE_NUMBER) {
        return new Error("Parameter of minus (-) must be number");
    }
    if (e->getNumberOfVariables() == 1) {
        return new Number(0 - ((Number*) parameter->value)->value);
    }
    int sum = ((Number*) parameter->value)->value;
    for (int i = 1; i < e->getNumberOfVariables(); i++) {
        Variable *parameter = e->getVariable(Environment::varNameAt(i));
        if (parameter->value->dataType() == DataType::TYPE_NUMBER) {
            sum -= ((Number*) parameter->value)->value;
        } else {
            return new Error("Parameter of minus (-) must be number");
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

string BuildInMultiplication::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

DataType* BuildInMultiplication::eval(Environment *e) {
    int sum = 0;
    for (int i = 0; i < e->getNumberOfVariables(); i++) {
        Variable *parameter = e->getVariable(Environment::varNameAt(i));
        if (parameter->value->dataType() == DataType::TYPE_NUMBER) {
            if (i == 0) {
                sum = ((Number*) parameter->value)->value;
            } else {
                sum *= ((Number*) parameter->value)->value;
            }
        } else {
            return new Error("Parameter of multiplication (*) must be number");
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

string BuildInDefconst::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

DataType* BuildInDefconst::eval(Environment *e) {
    if (checkArgCount(e->getNumberOfVariables())) {
        return new Error("Wrong number of arguments of defconst, requered 2");
    }
    //definuje premenn v environmente funkcie z ktorej bola volana
    Function *parentFunction = LispStack::getInstance().pop();
    if (parentFunction != NULL) {
        parentFunction->functionEnvironment->addVariable(((String*) e->getVariable(Environment::varNameAt(0))->value)->value,
                e->getVariable(Environment::varNameAt(1))->value, true);
    }
    return new Void();
}

BuildInList::BuildInList() {
    name = "list";
}

string BuildInList::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

bool BuildInList::checkArgCount(int givenArgCount) {
    return true;
}

DataType* BuildInList::eval(Environment *e) {
    List *list = new List();
    for (int i = 0; i < e->getNumberOfVariables(); i++) {
        list->addElement(e->getVariable(Environment::varNameAt(i)));
    }
    return list;
}

/*
 * Definition of equality
 */
BuildInEqual::BuildInEqual() {
    name = "==";
}

string BuildInEqual::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

bool BuildInEqual::checkArgCount(int givenArgCount) {
    return givenArgCount > 1;
}

/*
 * Easy equality comparison (working for almost all cases):
 *   1. Compare types (should be same)
 *   2. Compare string values (should be same)
 */
DataType* BuildInEqual::eval(Environment *e) {
    if (e->getNumberOfVariables() < 2) {
        return new Error("Wrong number of arguments of ==");
    }
    Variable *pattern = e->getVariable(Environment::varNameAt(0));
    int valueType = pattern->value->dataType();
    string valueString = pattern->value->toString();
    for (int i = 1; i < e->getNumberOfVariables(); i++) {
        Variable *p2 = e->getVariable(Environment::varNameAt(i));
        if(valueType != p2->value->dataType()
                || valueString.compare(p2->value->toString()) != 0)
            return new False();
    }
    return new True();
}





