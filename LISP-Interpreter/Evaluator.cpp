/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Evaluator.cpp
 * Author: phil
 * 
 * Created on Nedeľa, 2017, januára 29, 9:03
 */

#include "Evaluator.h"

Evaluator::Evaluator() {
}

Evaluator::Evaluator(const Evaluator& orig) {
}

Evaluator::~Evaluator() {
}

DataType* Evaluator::eval(Array* tokens, Enviroment& e) {
    return tokens->eval(e);
}
