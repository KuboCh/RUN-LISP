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
void Nil::eval() {
    //    return NULL;
}

void Nil::print(){
    cout << "nil" << endl;
}
