/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parametr.cpp
 * Author: jakub
 * 
 * Created on Utorok, 2017, januára 10, 14:02
 */

#include "Parametr.h"

Parametr::Parametr(){
    
}

Parametr::Parametr(string name, DataType *value, bool constant) {
    this->name = name;
    this->value = value;
    this->constant = constant;
}

Parametr::Parametr(const Parametr& orig) {
}

Parametr::~Parametr() {
}

void Parametr::eval() {
    value->eval();
}

void Parametr::print(){
    value->print();
}


