#include <algorithm>

#include "True.h"

True::True() {
}

True::True(const True& orig) {
}

True::~True() {
}

/*
 * True is (surprisingly) true.
 */
DataType* True::eval(Enviroment& e) {
    return this;
}

void True::print(){
    cout << "true";
}
