/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ParserTest.cpp
 * Author: phil
 *
 * Created on 27.1.2017, 9:47:03
 */

#include "ParserTest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ParserTest);

ParserTest::ParserTest() {
}

ParserTest::~ParserTest() {
}

void ParserTest::setUp() {
    e.addFunction(new BuildInPlus());
    e.addFunction(new BuildInDefconst());
    e.addFunction(new BuildInDefvar());
    e.addFunction(new BuildInList());
    e.addFunction(new BuildInMinus());
    e.addFunction(new BuildInMultiplication());
}

void ParserTest::tearDown() {
}

void ParserTest::testBasicDataTypes() {
    DataType* d = p.parse("145123", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_NUMBER);
    CPPUNIT_ASSERT(((Number*) d)->value == 145123);

    d = p.parse("\"Hello world!\"", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_STRING);
    CPPUNIT_ASSERT(((String*) d)->value == "Hello world!");

    d = p.parse("nil", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_NIL);
    CPPUNIT_ASSERT(((Nil*) d)->toString() == "nil");

    d = p.parse("true", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_TRUE);
    CPPUNIT_ASSERT(((True*) d)->toString() == "true");

    d = p.parse("false", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_FALSE);
    CPPUNIT_ASSERT(((False*) d)->toString() == "false");
}

void ParserTest::testBasicVariables() {
    p.pushBack(" a 5)\n");
    DataType* d = p.parse("(defvar", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_PARAMETR);
    Variable* v = (Variable*) d;
    CPPUNIT_ASSERT(v->name == "a");
    CPPUNIT_ASSERT(v->constant == false);
    CPPUNIT_ASSERT(v->value->dataType() == d->TYPE_NUMBER);
    Number* n = (Number*) v->value;
    CPPUNIT_ASSERT(n->value == 5);
    // Reading variables
    d = p.parse("a", &e);
    v = (Variable*) d;
    CPPUNIT_ASSERT(v->name == "a");
    CPPUNIT_ASSERT(v->constant == false);
    CPPUNIT_ASSERT(v->value->dataType() == d->TYPE_NUMBER);
    n = (Number*) v->value;
    CPPUNIT_ASSERT(n->value == 5);
    
    p.pushBack(" b 5)\n");
    d = p.parse("(defconst", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_PARAMETR);
    v = (Variable*) d;
    CPPUNIT_ASSERT(v->name == "b");
    CPPUNIT_ASSERT(v->constant == true);
    CPPUNIT_ASSERT(v->value->dataType() == d->TYPE_NUMBER);
    n = (Number*) v->value;
    CPPUNIT_ASSERT(n->value == 5);
    // reading consts
    d = p.parse("b", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_PARAMETR);
    v = (Variable*) d;
    CPPUNIT_ASSERT(v->name == "b");
    CPPUNIT_ASSERT(v->constant == true);
    CPPUNIT_ASSERT(v->value->dataType() == d->TYPE_NUMBER);
    n = (Number*) v->value;
    CPPUNIT_ASSERT(n->value == 5);
}

// Space before last )
void ParserTest::testBasicVariablesWithSpace() {
    p.pushBack(" a 5 )\n");
    DataType* d = p.parse("(defvar", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_PARAMETR);
    Variable* v = (Variable*) d;
    CPPUNIT_ASSERT(v->name == "a");
    CPPUNIT_ASSERT(v->constant == false);
    CPPUNIT_ASSERT(v->value->dataType() == d->TYPE_NUMBER);
    Number* n = (Number*) v->value;
    CPPUNIT_ASSERT(n->value == 5);
    // Reading variables
    d = p.parse("a", &e);
    v = (Variable*) d;
    CPPUNIT_ASSERT(v->name == "a");
    CPPUNIT_ASSERT(v->constant == false);
    CPPUNIT_ASSERT(v->value->dataType() == d->TYPE_NUMBER);
    n = (Number*) v->value;
    CPPUNIT_ASSERT(n->value == 5);
    
    p.pushBack(" b 5 )\n");
    d = p.parse("(defconst", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_PARAMETR);
    v = (Variable*) d;
    CPPUNIT_ASSERT(v->name == "b");
    CPPUNIT_ASSERT(v->constant == true);
    CPPUNIT_ASSERT(v->value->dataType() == d->TYPE_NUMBER);
    n = (Number*) v->value;
    CPPUNIT_ASSERT(n->value == 5);
    // reading consts
    d = p.parse("b", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_PARAMETR);
    v = (Variable*) d;
    CPPUNIT_ASSERT(v->name == "b");
    CPPUNIT_ASSERT(v->constant == true);
    CPPUNIT_ASSERT(v->value->dataType() == d->TYPE_NUMBER);
    n = (Number*) v->value;
    CPPUNIT_ASSERT(n->value == 5);
}

void ParserTest::testBasicLists(){
    p.pushBack(" 1 2 3 4 5 6)\n");
    DataType* d = p.parse("(list", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_LIST);
    List* v = (List*) d;
    CPPUNIT_ASSERT(v->toString() == "(1 2 3 4 5 6)");
    
    p.pushBack(" a 5 )\n");
    p.parse("(defvar", &e);
    p.pushBack(" a 2 a 4 a 6)\n");
    d = p.parse("(list", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_LIST);
    v = (List*) d;
    CPPUNIT_ASSERT(v->toString() == "(5 2 5 4 5 6)");
}

void ParserTest::testBasicFunctions(){
    p.pushBack(" plus (x y) (+ x y))\n");
    DataType* d = p.parse("(def", &e);
    
    p.pushBack(" 1 2)\n");
    DataType* r = p.parse("(plus", &e);
    CPPUNIT_ASSERT(r->dataType() == r->TYPE_NUMBER);
    CPPUNIT_ASSERT(((Number*) r)->value == 3);
    
    // function calling function
    p.pushBack(" inc (x) (plus x 1))\n");
    d = p.parse("(def", &e);
    
    p.pushBack(" 1)\n");
    r = p.parse("(inc", &e);
    CPPUNIT_ASSERT(r->dataType() == r->TYPE_NUMBER);
    CPPUNIT_ASSERT(((Number*) r)->value == 2);
    
    // function calling function and defconst
    p.pushBack(" inc (x) (defconst one 1) (plus x one))\n");
    d = p.parse("(def", &e);
    
    p.pushBack(" 1)\n");
    r = p.parse("(inc", &e);
    CPPUNIT_ASSERT(r->dataType() == r->TYPE_NUMBER);
    CPPUNIT_ASSERT(((Number*) r)->value == 2);
    
    // Constant "one" should not exist in main environment now
    d = p.parse("one", &e);
    CPPUNIT_ASSERT(d->dataType() == d->TYPE_ERROR);
    
    // TODO FAIL!
    // f in f in f ...
    p.pushBack(" inc4 (x) (inc (inc (inc (inc x)))))\n");
    d = p.parse("(def", &e);
    
    p.pushBack(" 0)\n");
    r = p.parse("(inc", &e);
    CPPUNIT_ASSERT(r->dataType() == r->TYPE_NUMBER);
    CPPUNIT_ASSERT(((Number*) r)->value == 4);
    
    // TODO FAIL!
    // f in f with defvars defconsts...
    p.pushBack(" inc4 (x) (defvar a x) (defconst one 1) (inc a one) (inc a one) (inc a one) (inc a one) (a))\n");
    d = p.parse("(def", &e);
    
    p.pushBack(" 0)\n");
    r = p.parse("(inc", &e);
    CPPUNIT_ASSERT(r->dataType() == r->TYPE_NUMBER);
    CPPUNIT_ASSERT(((Number*) r)->value == 4);
}

