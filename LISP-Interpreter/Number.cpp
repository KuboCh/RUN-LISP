#include "Number.h"

Number::Number() {
}

Number::Number(int val) {
    value = val;
}

Number::Number(const Number& orig) {
}

Number::~Number() {
}

void Number::eval() {
    // Number is already evaluated (atomic value)
}