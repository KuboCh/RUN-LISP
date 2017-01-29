#include "Void.h"

Void::Void() {
}

Void::Void(const Void& orig) {
}

Void::~Void() {
}

void Void::print() {
    cout << "";
}

DataType* Void::eval(Enviroment& e) {
    return this;
}

