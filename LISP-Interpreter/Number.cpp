#include "Number.h"
#include <sstream>

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

void Number::print(){
    cout << value;
}

string Number::toString(){
    stringstream ss;
    ss << value;
    string str;
    ss >> str;
    return str;
}
