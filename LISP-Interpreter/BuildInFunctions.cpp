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
#include "False.h"
#include "True.h"
#include "Nil.h"
#include "Parser.h"

BuildInPlus::BuildInPlus() {
    name = "+";
}

BuildInPlus::~BuildInPlus() {
}

int highestOneBitPosition(unsigned long int number) {
    int bits = 0;
    while (number != 0) {
        ++bits;
        number >>= 1;
    };
    return bits;
}

bool multiplication_is_safe(unsigned long int a, unsigned long int b) {
    int a_bits = highestOneBitPosition(a), b_bits = highestOneBitPosition(b);
    return (a_bits + b_bits <= 64);
}

bool addition_is_safe(unsigned long int a, unsigned long int b) {
    int a_bits = highestOneBitPosition(a), b_bits = highestOneBitPosition(b);
    return (a_bits < 64 && b_bits < 64);
}

DataType* BuildInPlus::sumNubers(Environment *e) {
    unsigned long int sum = 0;
    for (int i = 0; i < e->getNumberOfVariables(); i++) {
        Variable *parameter = e->getVariable(Environment::varNameAt(i));
        if (parameter->value->dataType() == DataType::TYPE_NUMBER) {
            if (!addition_is_safe(sum, ((Number*) parameter->value)->value))
                return new Error("Number overflow.");
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
    LispStack::getInstance().push(parentFunction);
    return new Nil();
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
    unsigned long int sum = 0;
    for (int i = 0; i < e->getNumberOfVariables(); i++) {
        Variable *parameter = e->getVariable(Environment::varNameAt(i));
        if (parameter->value->dataType() == DataType::TYPE_NUMBER) {
            if (i == 0) {
                sum = ((Number*) parameter->value)->value;
            } else {
                if (!multiplication_is_safe(sum, ((Number*) parameter->value)->value))
                    return new Error("Number overflow.");
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
    LispStack::getInstance().push(parentFunction);
    return new Nil();
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
        if (valueType != p2->value->dataType()
                || valueString.compare(p2->value->toString()) != 0) {
            if (Parser::PRINT)
                cout << "== false" << endl;
            return new False();
        }
    }
    if (Parser::PRINT)
        cout << "== true" << endl;
    return new True();
}

/*
 * Definition of <
 */
BuildInLower::BuildInLower() {
    name = "<";
}

bool BuildInLower::checkArgCount(int givenArgCount) {
    return givenArgCount == 2;
}

string BuildInLower::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

DataType* BuildInLower::eval(Environment *e) {
    if (e->getNumberOfVariables() != 2) {
        return new Error("Wrong number of arguments of <");
    }
    Variable *arg1 = e->getVariable(Environment::varNameAt(0));
    Variable *arg2 = e->getVariable(Environment::varNameAt(1));
    if (arg1->value->dataType() == arg2->value->dataType()) {
        if (arg1->value->dataType() == DataType::TYPE_NUMBER) {
            Number* arg1n = (Number*) arg1;
            Number* arg2n = (Number*) arg2;
            if (arg1n->value < arg2n->value) {
                if (Parser::PRINT)
                    cout << "< true" << endl;
                return new True();
            } else {
                if (Parser::PRINT)
                    cout << "< false" << endl;
                return new False();
            }
        } else {
            string arg1s = arg1->toString();
            string arg2s = arg2->toString();
            if (arg1s.compare(arg2s) < 0) {
                if (Parser::PRINT)
                    cout << "< true" << endl;
                return new True();
            } else {
                if (Parser::PRINT)
                    cout << "< false" << endl;
                return new False();
            }
        }
    } else {
        return new Error("Arguments of < should be of the same type.");
    }
}

/*
 * Definition of >
 */
BuildInGreater::BuildInGreater() {
    name = ">";
}

bool BuildInGreater::checkArgCount(int givenArgCount) {
    return givenArgCount == 2;
}

string BuildInGreater::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

DataType* BuildInGreater::eval(Environment *e) {
    if (e->getNumberOfVariables() != 2) {
        return new Error("Wrong number of arguments of >");
    }
    Variable *arg1 = e->getVariable(Environment::varNameAt(0));
    Variable *arg2 = e->getVariable(Environment::varNameAt(1));
    if (arg1->value->dataType() == arg2->value->dataType()) {
        if (arg1->value->dataType() == DataType::TYPE_NUMBER) {
            Number* arg1n = (Number*) arg1->value;
            Number* arg2n = (Number*) arg2->value;
            if (arg1n->value > arg2n->value)
                return new True();
            else return new False();
        } else {
            string arg1s = arg1->toString();
            string arg2s = arg2->toString();
            if (arg1s.compare(arg2s) > 0)
                return new True();
            else return new False();
        }
    } else {
        return new Error("Arguments of > should be of the same type.");
    }
}

/*
 * Definition of &&
 */
BuildInAnd::BuildInAnd() {
    name = "&&";
}

bool BuildInAnd::checkArgCount(int givenArgCount) {
    return givenArgCount > 0;
}

string BuildInAnd::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

DataType* BuildInAnd::eval(Environment *e) {
    if (e->getNumberOfVariables() == 0) {
        return new Error("Wrong number of arguments of &&");
    }
    for (int i = 0; i < e->getNumberOfVariables(); i++) {
        Variable *v = e->getVariable(Environment::varNameAt(i));
        DataType *val = v->eval(e);
        if (val->dataType() != DataType::TYPE_TRUE && val->dataType() != DataType::TYPE_FALSE)
            return new Error("Arguments should be of type Boolean (true/false)." + val->typeToString());
        if (val->dataType() == DataType::TYPE_FALSE)
            return new False();
    }
    return new True();
}

/*
 * Definition of ||
 */
BuildInOr::BuildInOr() {
    name = "||";
}

bool BuildInOr::checkArgCount(int givenArgCount) {
    return givenArgCount > 0;
}

string BuildInOr::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

DataType* BuildInOr::eval(Environment *e) {
    if (e->getNumberOfVariables() == 0) {
        return new Error("Wrong number of arguments of ||");
    }
    for (int i = 0; i < e->getNumberOfVariables(); i++) {
        Variable *v = e->getVariable(Environment::varNameAt(i));
        DataType *val = v->eval(e);
        if (val->dataType() != DataType::TYPE_TRUE && val->dataType() != DataType::TYPE_FALSE)
            return new Error("Arguments should be of type Boolean (true/false)." + val->typeToString());
        if (val->dataType() == DataType::TYPE_TRUE)
            return new True();
    }
    return new False();
}

/*
 * Definition of undef
 */
BuildInUndef::BuildInUndef() {
    name = "undef";
}

bool BuildInUndef::checkArgCount(int givenArgCount) {
    return givenArgCount > 0;
}

string BuildInUndef::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

DataType* BuildInUndef::eval(Environment *e) {
    if (e->getNumberOfVariables() == 0) {
        return new Error("Nothing to undef.");
    }
    bool removed = false;
    for (int i = 0; i < e->getNumberOfVariables(); i++) {
        Variable *v = e->getVariable(Environment::varNameAt(i));
        if (v->value) {
            string name = v->value->toString();
            stack<Function*> stackOfFunctions;
            while (!LispStack::getInstance().isEmpty()) { // go through stack
                Function* f = LispStack::getInstance().pop();
                stackOfFunctions.push(f);
                if (f->functionEnvironment->removeVariable(name)) {
                    removed = true;
                    break;
                }
                if (f->functionEnvironment->removeFunction(name)) {
                    removed = true;
                    break;
                }
            }
            while (!stackOfFunctions.empty()) { // push it back
                Function* f = stackOfFunctions.top();
                stackOfFunctions.pop();
                LispStack::getInstance().push(f);
            }
        }
    }
    if (removed)
        return new True();
    else return new False();
}

BuildInIf::BuildInIf() {
    name = "if";
}

string BuildInIf::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

bool BuildInIf::checkArgCount(int givenArgCount) {
    return givenArgCount == 3;
}

/*
 * 
 * 
 * 
 */
DataType* BuildInIf::eval(Environment *e) {
    throw "error eval of if function";
}

BuildInFor::BuildInFor() {
    name = "for";
}

string BuildInFor::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

bool BuildInFor::checkArgCount(int givenArgCount) {
    return givenArgCount > 3;
}

/*
 * 
 * 
 * 
 */
DataType* BuildInFor::eval(Environment *e) {
    throw "error eval of for function";
}

BuildInOut::BuildInOut() {
    name = "out";
}

string BuildInOut::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

bool BuildInOut::checkArgCount(int givenArgCount) {
    return givenArgCount == 1;
}

/*
 * 
 * 
 * 
 */
DataType* BuildInOut::eval(Environment *e) {
    if (e->getNumberOfVariables() != 1) {
        return new Error("Wrong number of arguments of out");
    }
    Variable *toPrint = e->getVariable(Environment::varNameAt(0));
    cout << toPrint->value->toString() << endl;
    return new Nil();
}

BuildInReturn::BuildInReturn() {
    name = "return";
}

string BuildInReturn::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

bool BuildInReturn::checkArgCount(int givenArgCount) {
    return givenArgCount == 1;
}

/*
 * 
 * 
 * 
 */
DataType* BuildInReturn::eval(Environment *e) {
    //    if (e->getNumberOfVariables() != 1) {
    //        return new Error("Wrong number of arguments of out");
    //    }
    //    Variable *toPrint = e->getVariable(Environment::varNameAt(0));
    //    cout << toPrint->value->toString() << endl;
    //    return new Nil();
    throw "error eval of return function";
}

BuildInAt::BuildInAt() {
    name = "at";
}

string BuildInAt::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

bool BuildInAt::checkArgCount(int givenArgCount) {
    return givenArgCount == 2;
}

/*
 * 
 * 
 * 
 */
DataType* BuildInAt::eval(Environment *e) {
    Variable *l = e->getVariable(Environment::varNameAt(0));
    if (l->value->dataType() != DataType::TYPE_LIST) {
        return new Error("Wrong parameter of at, expected list");
    }
    DataType *poz = e->getVariable(Environment::varNameAt(1))->eval(e);
    if (poz->dataType() != DataType::TYPE_NUMBER) {
        return new Error("Wrong parameter of at, expected number");
    }
    List *newList = (List*) l->value;
    int position = ((Number*) poz)->value;
    if (newList->elements.size() <= position || position < 0) {
        return new Error("Wrong position at at");
    }
    if (Parser::PRINT)
        cout << "at " << newList->elements[position]->toString() << endl;
    return newList->elements[position]->eval(e);
}

BuildInSet::BuildInSet() {
    name = "set";
}

string BuildInSet::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

bool BuildInSet::checkArgCount(int givenArgCount) {
    return givenArgCount == 3;
}

/*
 * 
 * 
 * 
 */
DataType* BuildInSet::eval(Environment *e) {
    Variable *l = e->getVariable(Environment::varNameAt(0));
    if (l->value->dataType() != DataType::TYPE_LIST) {
        return new Error("Wrong parameter of set, expected list");
    }
    DataType *poz = e->getVariable(Environment::varNameAt(1))->eval(e);
    if (poz->dataType() != DataType::TYPE_NUMBER) {
        return new Error("Wrong parameter of set, expected number");
    }
    List *newList = (List*) l->value;
    int position = ((Number*) poz)->value;
    if (newList->elements.size() <= position || position < 0) {
        return new Error("Wrong position at set");
    }
    newList->elements[position] = e->getVariable(Environment::varNameAt(2))->value;
    if (Parser::PRINT)
        cout << "set " << newList->toString() << endl;
    return newList;
}

BuildInDelete::BuildInDelete() {
    name = "delete";
}

string BuildInDelete::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

bool BuildInDelete::checkArgCount(int givenArgCount) {
    return givenArgCount == 2;
}

/*
 * 
 * 
 * 
 */
DataType* BuildInDelete::eval(Environment *e) {
    Variable *l = e->getVariable(Environment::varNameAt(0));
    if (l->value->dataType() != DataType::TYPE_LIST) {
        return new Error("Wrong parameter of delete, expected list");
    }
    DataType *poz = e->getVariable(Environment::varNameAt(1))->eval(e);
    if (poz->dataType() != DataType::TYPE_NUMBER) {
        return new Error("Wrong parameter of delete, expected number");
    }
    List *newList = (List*) l->value;
    int position = ((Number*) poz)->value;
    if (newList->elements.size() <= position || position < 0) {
        return new Error("Wrong position at delete");
    }
    newList->elements.erase(newList->elements.begin() + position);
    return newList;
}

BuildInAdd::BuildInAdd() {
    name = "add";
}

string BuildInAdd::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

bool BuildInAdd::checkArgCount(int givenArgCount) {
    return givenArgCount == 2;
}

/*
 * 
 * 
 * 
 */
DataType* BuildInAdd::eval(Environment *e) {
    Variable *l = e->getVariable(Environment::varNameAt(0));
    if (l->value->dataType() != DataType::TYPE_LIST) {
        return new Error("Wrong parameter of add, expected list");
    }
    DataType *value = e->getVariable(Environment::varNameAt(1))->eval(e);
    List *newList = (List*) l->value;
    newList->elements.push_back(value);
    return newList;
}

BuildInLength::BuildInLength() {
    name = "length";
}

string BuildInLength::getParameterNameAt(int position) {
    return Environment::varNameAt(position);
}

bool BuildInLength::checkArgCount(int givenArgCount) {
    return givenArgCount == 1;
}

/*
 * 
 * 
 * 
 */
DataType* BuildInLength::eval(Environment *e) {
    Variable *l = e->getVariable(Environment::varNameAt(0));
    if (l->value->dataType() != DataType::TYPE_LIST) {
        return new Error("Wrong parameter of lenght, expected list");
    }
    return new Number(((List*) l->value)->elements.size());
}
