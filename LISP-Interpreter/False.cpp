#include "False.h"

False::False() {
}

False::False(const False& orig) {
}

False::~False() {
}

/*
 * False is (surprisingly) false.
 */
DataType* False::eval(Enviroment& e) {
    return this;
}

void False::print(){
    cout << "false";
}
