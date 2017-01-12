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

void String::eval() {
    // String is already evaluated (atomic value)
}

void String::print() {
    cout << value;
}
