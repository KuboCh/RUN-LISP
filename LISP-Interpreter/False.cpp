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
void False::eval() {
    //    return false;
}

void False::print(){
    cout << "false";
}
