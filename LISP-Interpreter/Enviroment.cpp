/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enviroment.cpp
 * Author: jakub
 * 
 * Created on Utorok, 2017, januára 10, 13:57
 */

#include "Enviroment.h"
#include "Parametr.h"
#include "Error.h"
#include "Function.h"

Enviroment::Enviroment() {
}

Enviroment::Enviroment(const Enviroment& orig) {
}

Enviroment::~Enviroment() {
}

Parametr* Enviroment::getParametr(string name) {
    if (parametrs.find(name) == parametrs.end()){
        return NULL;
    }
    return parametrs[name];
}

DataType* Enviroment::addParametr(string name, DataType *value, bool isConstant) {
    map<string, Parametr*>::iterator it = parametrs.find(name);
    if (it != parametrs.end()){
        if (it->second->constant) {
            return new Error("Can't change value of constant");
        }
        it->second->value = value;
        it->second->constant = isConstant;
        return it->second;
    }
    Parametr *newParametr = new Parametr(name, value, isConstant);
    parametrs[name] = newParametr;
    numberOfParametrs++;
    return newParametr;
}

map<string, Parametr*>::const_iterator Enviroment::getParametrsIterator(){ 
    return parametrs.begin();
}
 
map<string, Parametr*>::const_iterator Enviroment::getParametrsIteratorEnd() {
    return parametrs.end();
}

Function* Enviroment::addFunction(Function* function) {
    //TODO kontrola ci uz take nahodou neexistuje
    functions.push_back(function);
    return function;
}

Function* Enviroment::getFunction(string name) {
    for (vector<Function*>::iterator it = functions.begin(); it != functions.end(); it++){
        if ((*it)->name == name){
            return (*it);
        }
    }
    return NULL;
}

int Enviroment::getNumberOfParametrs() {
    return numberOfParametrs;
}
