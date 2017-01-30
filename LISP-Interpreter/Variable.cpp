#include "Variable.h"

Variable::Variable(){
    
}

Variable::Variable(string name, DataType *value, bool constant) {
    this->name = name;
    this->value = value;
    this->constant = constant;
}

Variable::Variable(const Variable& orig) {
}

Variable::~Variable() {
}

DataType* Variable::eval(Environment& e) {
    return value->eval(e);
}

void Variable::print(){
    value->print();
}


