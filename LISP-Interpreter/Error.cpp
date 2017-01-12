#include "Error.h"

using namespace std;

Error::Error() {
}

Error::Error(string errorMessage) {
    this->errorMessage = errorMessage;
}

Error::Error(const Error& orig) {
}

Error::~Error() {
}

void Error::eval() {
    //TODO return
}

void Error::print(){
    cout << "Exception: " << errorMessage << endl;
}

string Error::toString() {
    return errorMessage;
}

