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

void Variable::eval() {
    value->eval();
}

void Variable::print(){
    value->print();
}


