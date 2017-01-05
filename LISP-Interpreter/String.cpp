/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   String.cpp
 * Author: phil
 * 
 * Created on Štvrtok, 2017, januára 5, 21:09
 */

#include "String.h"

String::String() {
}

String::String(string s) {
    value = s;
}

String::String(const String& orig) {
}

String::~String() {
}

void String::eval() {
    // String is already evaluated (atomic value)
}

void String::print(){
    cout << value << endl;
}
