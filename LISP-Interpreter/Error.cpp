#include "Error.h"
#include "DataType.h"

Error::Error() {
}

Error::Error(string errorMessage) {
    this->errorMessage = errorMessage;
}

Error::Error(const Error& orig) {
}

Error::~Error() {
}

DataType* Error::eval(Environment* e) {
    return this;
}

void Error::print(){
    cout << "Exception: " << errorMessage << endl;
}

string Error::toString() {
    return errorMessage;
}

