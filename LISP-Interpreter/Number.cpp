#include "Number.h"
#include <sstream>

Number::Number() {
}

Number::Number(unsigned long int val) {
    value = val;
}

Number::Number(const Number& orig) {
}

Number::~Number() {
}

DataType* Number::eval(Environment* e) {
    return this;
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
