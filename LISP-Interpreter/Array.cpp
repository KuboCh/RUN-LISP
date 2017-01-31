#include "Array.h"
#include "Environment.h"
#include "Function.h"
#include "Parameter.h"
#include "LispStack.h"
#include "Number.h"
#include "Nil.h"
#include "Variable.h"
#include "String.h"
#include "Memory.h"

Array::Array() {
}

Array::Array(const Array& orig) {
}

Array::~Array() {
}

string Array::toString() {
    string s = "[";
    for (int i = 0; i != a.size(); i++) {
        s += a[i]->toString();
    }
    s += "]";
    return s;
}

/*
 *  Assumed array for function call:
 *  (name param1 param2 param3 ...)
 *  @param param1, param2, param3, ... are Arrays (can be another function), can be evaluated
 *  @Examples (+ 1 2 3 4 5)
 *    (+ 5 (- 3 2))
 *    (+ x (- x 1))
 */
DataType* Array::callFunction(Environment* e) {
    Function *function = e->getFunction((*this)[0]);
    Environment *functionEnvironment = Memory::getInstance().get(); //new Environment();// 
    if (function == NULL) {
        cout << "Call to undefined function " << (*this)[0] << endl;
        return NULL;
    }
    // parametre by mali byt do konca tohoto array
    for (int i = 1; i < a.size(); i++) {
        DataType *p = a[i]->eval(e);
        if (p->dataType() == DataType::TYPE_PARAMETER) { // get value of this param
            p = p->eval(e);
        }
        //cout << "arg: " <<p->toString() << " of type " << p->typeToString() << endl;
        functionEnvironment->addVariable(function->getParameterNameAt(i - 1), p, false);
    }
    function->functionEnvironment = functionEnvironment;
    return function->eval(functionEnvironment);
}

pair<Function*, list<Parameter*> > Array::getInBodyFunction(Environment* e) {
    Function *function = e->getFunction((*this)[0]);
    if (!function)
        throw "Function " + (*this)[0] + " is not defined.";
    list<Parameter*> parameters;
    Parameter* param;
    for (int i = 1; i < a.size(); i++) {
        param = new Parameter();
        if (a[i]->isAtom()) {
            param->value = (DataType*) a[i];
            if (((DataType*) a[i])->dataType() == DataType::TYPE_SYMBOL) {
                //ak je funkcia defvar, defconst symbol sa zameni za string
                if ((function->name == "defvar" || function->name == "defconst") && i == 1) {
                    param->value = new String((*this)[i]);
                } else {
                    param->parameterName = (*this)[i]; // string of this param
                }
            }
        } else {
            pair<Function*, list<Parameter*> > ibf = a[i]->getInBodyFunction(e);
            param->function = ibf.first;
            param->parametersOfFunction = ibf.second;
        }
        parameters.push_back(param);
    }
    return pair<Function*, list<Parameter*> >(function, parameters);
}

/*
 * Assumed array for function reading:
 * (define name (Array of vars or blank)
 *      (function call with its params)
 *      (function call with its params)
 *      (function call with its params)
 *      ...
 * )
 */
DataType* Array::defFunction(Environment *e) {
    Function *function = new Function((*this)[1]);
    // Set function arguments
    if (!a[2]->isAtom()) {
        for (int i = 0; i < a[2]->a.size(); i++) {
            function->addArgument((*a[2])[i]); // i-th name of argument Array*
        }
    } else {
        throw "Function should have array of arguments (atom given).";
    }
    // Now set functions in body!
    for (int i = 3; i < a.size(); i++) { // for each body function get params and add
        if (!a[i]->isAtom()) {
            function->addToBody(a[i]->getInBodyFunction(e));
        } else {
            throw "Wrong declaration of body function (atom given).";
        }
    }
    e->addFunction(function);
    return (DataType*) a[1]; // symbol for this function
}

/*
 * Conditional test
 * @Format (if (test) (conseq) (alt))
 * @returns result value of conseq/alt
 */
DataType* Array::processIf(Environment* e) {
    if (a.size() != 4)
        throw "Wrong number of conditional (if).";
    DataType * condResult;
    if (a[1]->isAtom()) {
        condResult = (DataType*) a[1];
    } else {
        condResult = a[1]->eval(e);
    }
    if (condResult->dataType() == DataType::TYPE_TRUE) {
        return a[2]->eval(e);
    } else if (condResult->dataType() == DataType::TYPE_FALSE) {
        return a[3]->eval(e);
    } else
        throw "Conditional result should be true or false, is " + condResult->typeToString();
    return new Nil();
}

/*
 * Loop control
 * @Format (for var from A to B do
 *      (action1) 
 *      (action2) 
 *      ...
 *     )
 */
DataType* Array::processLoop(Environment* e) {
    if (a.size() < 7 || a[2]->toString().compare("from") != 0
            || a[4]->toString().compare("to") != 0
            || a[6]->toString().compare("do") != 0)
        throw "Wrong defintion of loop parameters";
    DataType* from = a[3]->eval(e);
    DataType* to = a[5]->eval(e);
    if (from->dataType() != DataType::TYPE_NUMBER
            || to->dataType() != DataType::TYPE_NUMBER)
        throw "Loop bounds should be of type number.";
    Number *fromN = (Number*) from;
    Number *toN = (Number*) to;
    DataType* var = e->addVariable(a[1]->toString(), fromN, true);
    Number* varN = (Number*) ((Variable*) var)->value;
    DataType* result = new Nil();
    for (int i = fromN->value; i < toN->value; i++) {
        cout << "i=" << varN->value << endl;
        for (int j = 7; j < a.size(); j++) { // perform body functions
            result = a[j]->eval(e);
        }
        varN->value++;
    }
    return result;
}

DataType* Array::undefFunction(Environment *e) {
    Function *function = e->getFunction((*this)[0]);
    function->functionEnvironment = Memory::getInstance().get(); //new Environment();// 
    if (function == NULL) {
        cout << "Call to undefined function " << (*this)[0] << endl;
        return NULL;
    }
    // parametre by mali byt do konca tohoto array
    for (int i = 1; i < a.size(); i++) {
        if (a[i]->isAtom() && ((DataType*) a[i])->dataType() != DataType::TYPE_SYMBOL)
            throw "Wrong argument type for undef.";
        function->functionEnvironment->addVariable(function->getParameterNameAt(i - 1), (Symbol*) a[i], false);
    }
    return function->eval(function->functionEnvironment);
}

/*
 * Eval of array = defvar/defconst/def function/call function.
 * Everything that's not array is an atom (symbol, string, number) and is evaluated separately.
 * Evaluation is runned in some environment (=set of functions and variables).
 * @returns DataType = Atomic value (string/number).
 */
DataType* Array::eval(Environment* e) {
    try {
        if (a.size() > 0) {
            string name = (*this)[0];
            if (name.compare("defvar") == 0) {
                if (a.size() == 3)
                    return e->addVariable(a[1]->toString(), a[2]->eval(e), false);
                else
                    cout << "(defvar name value)" << endl;
            } else if (name.compare("defconst") == 0) {
                if (a.size() == 3)
                    return e->addVariable(a[1]->toString(), a[2]->eval(e), true);
                else
                    cout << "(defconst name value)" << endl;
            } else if (name.compare("if") == 0) {
                return processIf(e);
            } else if (name.compare("for") == 0) {
                return processLoop(e);
            } else if (name.compare("def") == 0) {
                return defFunction(e);
            } else if (name.compare("undef") == 0) {
                return undefFunction(e);
            } else {
                return callFunction(e);
            }
        }
    } catch (string error) {
        cin.sync(); // clear cin?
        cout << error << endl;
        return NULL;
    } catch (char const * error) {
        cin.sync(); // clear cin?
        cout << error << endl;
        return NULL;
    }
    //cout << "Abstract Array eval() should be implemented." << endl;
    return NULL;
}