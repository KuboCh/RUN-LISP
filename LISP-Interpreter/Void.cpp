#include "Void.h"
#include "Environment.h"

Void::Void() {
}

Void::Void(const Void& orig) {
}

Void::~Void() {
}

void Void::print() {
    cout << "";
}

DataType* Void::eval(Environment& e) {
    return this;
}

