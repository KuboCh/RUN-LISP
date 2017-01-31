#include "False.h"
#include "DataType.h"
#include "Environment.h"

False::False() {
}

False::False(const False& orig) {
}

False::~False() {
}

/*
 * False is (surprisingly) false.
 */
DataType* False::eval(Environment* e) {
    return this;
}

void False::print(){
    cout << "false";
}
