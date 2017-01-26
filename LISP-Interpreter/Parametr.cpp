#include "Parametr.h"
#include "Error.h"
#include "String.h"

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

DataType* Parametr::eval(Enviroment *e){
    if (parametrName != "") {
        Variable *v = e->getVariable(parametrName);
        if (v == NULL) {
            //TODO ak sa nenaslo hladat v enviromentoch vyssie az potom ak sa nenajde return errror
            return new Error("Variable " + parametrName + " not declared");
        }
        return v->value;
    }
    if (value != NULL) {
        if (value->dataType() == DataType::TYPE_STRING){
            String *s = ((String*) value);
        }
        return value;
    }
    function->eval(e);
    //TODO eval funkciu - pripravit enviroment
    
}

int Parametr::getType(){
    if (parametrName != "") {
        return TYPE_VARIABLE_NAME;
    }
    if (value != NULL) {
        return TYPE_DATA_VALUE;
    }
    return TYPE_VARIABLE_NAME;
}