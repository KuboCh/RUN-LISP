#include "BuildInFunctions.h"
#include "Error.h"

BuildInPlus::BuildInPlus() {
    name = "+";
}

BuildInPlus::~BuildInPlus() {
}

DataType* BuildInPlus::sumNubers(Enviroment *e) {
    int sum = 0;
    for (int i = 0; i < e->getNumberOfParametrs(); i++) {
        Parametr *parametr = e->getParametr(Enviroment::varNameAt(i));
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
    for (int i = 0; i < e->getNumberOfParametrs(); i++) {
        Parametr *parametr = e->getParametr(Enviroment::varNameAt(i));
        sum += parametr->value->toString();
    }
    return new String(sum);
}

DataType* BuildInPlus::eval(Enviroment *e) {
    if (e->getNumberOfParametrs() < 2) {
        return new Error("Wrong number of arguments of +");
    }
    Parametr *parametr = e->getParametr(Enviroment::varNameAt(0));
    if (parametr->value->dataType() == DataType::TYPE_NUMBER) {
        return sumNubers(e);
    }
    return sumStrings(e);
}
