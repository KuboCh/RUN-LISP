#include "Evaluator.h"
#include "DataType.h"
#include "Array.h"
#include "Enviroment.h"

Evaluator::Evaluator() {
}

Evaluator::Evaluator(const Evaluator& orig) {
}

Evaluator::~Evaluator() {
}

DataType* Evaluator::eval(Array* tokens, Enviroment& e) {
    return tokens->eval(e);
}
