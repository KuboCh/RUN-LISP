#include "Array.h"
#include "Enviroment.h"
#include "Function.h"
#include "Parametr.h"

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
DataType* Array::callFunction(Enviroment& e) {
    Function *function = e.getFunction((*this)[0]);
    Enviroment *functionEnviroment = new Enviroment();
    if (function == NULL) {
        cout << "Call to undefined function " << (*this)[0] << endl;
        return NULL;
    }
    // parametre by mali byt do konca tohoto array
    try {
        for (int i = 1; i < a.size(); i++) {
            functionEnviroment->addVariable(function->getParametrNameAt(i - 1), a[i]->eval(e), false);
        }
    } catch (const char* error) {
        //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ???
        cin.sync(); // clear cin?
        cout << error << endl;
        return NULL;
    } catch (string error) {
        //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ???
        cin.sync(); // clear cin?
        cout << error << endl;
        return NULL;
    }
    return function->eval(functionEnviroment);
}

pair<Function*, list<Parametr*> > Array::getInBodyFunction(Enviroment& e) {
    Function *function = new Function();
    if (!e.getFunction((*this)[0]))
        throw "Function " + (*this)[0] + " is not defined.";
    list<Parametr*> parameters;
    Parametr* param;
    for (int i = 1; i < a.size(); i++) {
        param = new Parametr();
        if (a[i]->isAtom()) {
            param->value = (DataType*) a[i];
        } else {
            pair<Function*, list<Parametr*> > ibf = a[i]->getInBodyFunction(e);
            param->function = ibf.first;
        }
        parameters.push_back(param);
    }
    return pair<Function*, list<Parametr*> >(function, parameters);
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
DataType* Array::defFunction(Enviroment& e) {
    Function *function = new Function();
    if (e.getFunction((*this)[1]))
        throw "Function " + (*this)[1] + " is already defined.";
    function->name = (*this)[1];
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
        if (!a[i]->isAtom()) { // todo
            function->addToBody(a[i]->getInBodyFunction(e));
        } else {
            throw "Wrong declaration of body function (atom given).";
        }
    }
    e.addFunction(function);
    return (DataType*) a[1]; // symbol for this function
}

/*
 * Eval of array = defvar/defconst/def function/call function.
 * Everything that's not array is an atom (symbol, string, number) and is evaluated separately.
 * Evaluation is runned in some environment (=set of functions and variables).
 * @returns DataType = Atomic value (string/number).
 */
DataType* Array::eval(Enviroment& e) {
    if (a.size() > 0) {
        string name = (*this)[0];
        if (name.compare("defvar") == 0) {
            if (a.size() == 3) {
                return e.addVariable(a[1]->toString(), a[2]->eval(e), false);
            } else {
                cout << "(defvar name value)" << endl;
            }

        } else if (name.compare("defconst") == 0) {
            if (a.size() == 3) {
                return e.addVariable(a[1]->toString(), a[2]->eval(e), true);
            } else {
                cout << "(defconst name value)" << endl;
            }
        } else if (name.compare("def") == 0) { // TODO define function
            //cout << "Define function " << a[1]->toString() << endl;
            try {
                return defFunction(e);
            } catch (string error) {
                cin.sync(); // clear cin?
                cout << error << endl;
                return NULL;
            }
        } else {
            //cout << "Call function " << name << endl;
            try {
                return callFunction(e);
            } catch (string error) {
                cin.sync(); // clear cin?
                cout << error << endl;
                return NULL;
            }
        }
    }
    //cout << "Abstract Array eval() should be implemented." << endl;
    return NULL;
}