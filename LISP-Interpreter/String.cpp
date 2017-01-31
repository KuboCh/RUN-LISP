#include "String.h"

String::String() {
}

String::String(string s) {
    value = s;
}

String::String(const String& orig) {
}

String::~String() {
}

DataType* String::eval(Environment* e) {
    return this;
}

void String::print() {
    cout << '"' << value << '"';
}
