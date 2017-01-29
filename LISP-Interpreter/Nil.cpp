#include "Nil.h"

Nil::Nil() {
}

Nil::Nil(const Nil& orig) {
}

Nil::~Nil() {
}

/*
 * Nil is (surprisingly) nil.
 */
DataType* Nil::eval(Enviroment& e) {
    return this;
}

void Nil::print(){
    cout << "nil";
}
