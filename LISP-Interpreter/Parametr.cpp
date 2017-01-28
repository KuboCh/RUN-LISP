#include "Parametr.h"
#include "Error.h"
#include "String.h"
#include "LispStack.h"
#include "Number.h"

using namespace std;

Parametr::Parametr() {
}

Parametr::Parametr(const Parametr& orig) {
}

Parametr::~Parametr() {
}

//Parametr::Parametr(Function *function) {
//    this->function = function;
//    value = NULL;
//    parametrName = "";
//}
//
//Parametr::Parametr(DataType *value) {
//    function = NULL;
//    this->value = value;
//    parametrName = "";
//}
//
//Parametr::Parametr(string *name) {
//    function = NULL;
//    value = NULL;
//    parametrName = name;
//}

DataType* Parametr::eval(Enviroment *e) {
    if (parametrName != "") { // we have name, search for value in environments
        Variable *v = e->getVariable(parametrName);
        if (v == NULL) {
            //TODO ak sa nenaslo hladat v enviromentoch vyssie az potom ak sa nenajde return errror
            stack<Function*> tmpStack;
            while (v == NULL && !LispStack::getInstance().isEmpty()) {
                Function *f = LispStack::getInstance().pop();
                tmpStack.push(f);
                v = f->functionEnviroment->getVariable(parametrName);
            }
            if (v == NULL) {
                return new Error("Variable " + parametrName + " not declared");
            }
            while (!tmpStack.empty()) { // return all popped functions back on stack
                LispStack::getInstance().push(tmpStack.top());
                tmpStack.pop();
            }
        }
        cout << "Parameter " << parametrName << " is " << ((Number*) v->value)->value <<endl;
        return v->value;
    }
    if (value != NULL) {
        if (value->dataType() == DataType::TYPE_STRING) {
            String *s = ((String*) value); // um... wat? :D TODO?
        }
        return value;
    }
    cout << "Parametr value is result of function " << function->name << endl;
    return function->eval(e);
    //TODO eval funkciu - pripravit enviroment

}

int Parametr::getType() {
    if (parametrName != "") {
        return TYPE_VARIABLE_NAME;
    }
    if (value != NULL) {
        return TYPE_DATA_VALUE;
    }
    return TYPE_VARIABLE_NAME;
}