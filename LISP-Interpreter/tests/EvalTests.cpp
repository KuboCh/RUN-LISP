#include "EvalTests.h"
#include "../DataType.h"
#include "../Array.h"
#include "../BuildInFunctions.h"

CPPUNIT_TEST_SUITE_REGISTRATION(EvalTests);

EvalTests::EvalTests() {
}

EvalTests::~EvalTests() {
}

void EvalTests::setUp() {
    mainEnvironment = Memory::getInstance().get();
    mainFunction = new Function(mainEnvironment);
    LispStack::getInstance().push(mainFunction);
    mainEnvironment->addFunction(new BuildInPlus());
    mainEnvironment->addFunction(new BuildInDefconst());
    mainEnvironment->addFunction(new BuildInDefvar());
    mainEnvironment->addFunction(new BuildInUndef());
    mainEnvironment->addFunction(new BuildInList());
    mainEnvironment->addFunction(new BuildInMinus());
    mainEnvironment->addFunction(new BuildInMultiplication());
    mainEnvironment->addFunction(new BuildInEqual());
    mainEnvironment->addFunction(new BuildInLower());
    mainEnvironment->addFunction(new BuildInGreater());
    mainEnvironment->addFunction(new BuildInAnd());
    mainEnvironment->addFunction(new BuildInOr());
}

void EvalTests::tearDown() {
}

void EvalTests::testAtomEval() {
    result = parser.parse("1")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("1") == 0);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_NUMBER);
    result = parser.parse("true")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("true") == 0);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_TRUE);
    result = parser.parse("false")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("false") == 0);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_FALSE);
    result = parser.parse("nil")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("nil") == 0);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_NIL);
    result = parser.parse("\"str\"")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("\"str\"") == 0);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_STRING);
}

void EvalTests::testVariables() {
    result = parser.parse("(defvar x 5)\nx\n")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("5") == 0);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_PARAMETER);
    result = parser.parse("(defvar x (+ 5 5))\nx\n")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("10") == 0);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_PARAMETER);
    // Undef
    result = parser.parse("(defvar x (+ 5 5))")->eval(mainEnvironment);
    result = parser.parse("(undef x)")->eval(mainEnvironment);
    result = parser.parse("x")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_ERROR);
}

void EvalTests::testFunctions() {
    result = parser.parse("(def ++ (x) (+ x 1))")->eval(mainEnvironment);
    result = parser.parse("(++ 0)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("1") == 0);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_NUMBER);
    
    result = parser.parse("(++ (++ (++ 0)))")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("3") == 0);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_NUMBER);
}

void EvalTests::testIf() {
    result = parser.parse("1")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("1") == 0);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_NUMBER);
}

void EvalTests::testFor() {
    result = parser.parse("1")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("1") == 0);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_NUMBER);
}
