/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parametr.h
 * Author: jakub
 *
 * Created on Utorok, 2017, januára 10, 14:02
 */

#ifndef PARAMETR_H
#define PARAMETR_H

#include "DataType.h"


class Parametr : public DataType {
public:
    Parametr();
    Parametr(string name, DataType *value, bool constant);
    Parametr(const Parametr& orig);
    virtual ~Parametr();
    void eval();
    virtual void print();
    virtual int dataType() { return TYPE_PARAMETR; }
    DataType *value;
    string name;
    bool constant;
    string toString() { return value->toString(); }
private:
    
};

#endif /* PARAMETR_H */

