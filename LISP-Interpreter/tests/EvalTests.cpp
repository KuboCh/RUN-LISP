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
    mainEnvironment->addFunction(new BuildInIf());
    mainEnvironment->addFunction(new BuildInFor());
    mainEnvironment->addFunction(new BuildInOut());
    mainEnvironment->addFunction(new BuildInReturn());
    mainEnvironment->addFunction(new BuildInAt());
    mainEnvironment->addFunction(new BuildInSet());
    mainEnvironment->addFunction(new BuildInDelete());
    mainEnvironment->addFunction(new BuildInAdd());
    mainEnvironment->addFunction(new BuildInLength());
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
}

void EvalTests::testIf() {
    result = parser.parse("(if true true false)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("true") == 0);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_TRUE);

    result = parser.parse("(if (== 2 0) \"ok\" \"fail\")")->eval(mainEnvironment);
    cout << result->toString() << endl;
    CPPUNIT_ASSERT(result->toString().compare("\"fail\"") == 0);
    CPPUNIT_ASSERT(result->dataType() == DataType::TYPE_STRING);
}

void EvalTests::testFor() {
    result = parser.parse("(defvar x 0)")->eval(mainEnvironment);
    result = parser.parse("(for i from 1 to 10 do (defvar x i))")->eval(mainEnvironment);
    result = parser.parse("x")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("10") == 0);
}

void EvalTests::testList() {
    result = parser.parse("(defvar x (list 1 2 3 4 5))")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("(1 2 3 4 5)") == 0);
    result = parser.parse("(at x 0)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("1") == 0);
    result = parser.parse("(set x 4 false)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("(1 2 3 4 false)") == 0);
    result = parser.parse("(delete x 4)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("(1 2 3 4)") == 0);
    result = parser.parse("(add x 5)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("(1 2 3 4 5)") == 0);
    result = parser.parse("(length x)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("5") == 0);
}

void EvalTests::testFibonacci() {
    result = parser.parse("(def fib (n) (defvar p1 1) (defvar p2 1) (for i from 1 to (- n 1) do (defvar p3 (+ p1 p2)) (defvar p1 p2) (defvar p2 p3))(return p2))")->eval(mainEnvironment);
    result = parser.parse("(fib 1)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("1") == 0);
    result = parser.parse("(fib 2)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("1") == 0);
    result = parser.parse("(fib 3)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("2") == 0);
    result = parser.parse("(fib 4)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("3") == 0);
    result = parser.parse("(fib 5)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("5") == 0);
    result = parser.parse("(fib 6)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("8") == 0);
    result = parser.parse("(fib 7)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("13") == 0);
    result = parser.parse("(fib 8)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("21") == 0);
    result = parser.parse("(fib 9)")->eval(mainEnvironment);
    CPPUNIT_ASSERT(result->toString().compare("34") == 0);
}

void EvalTests::testSort() {
    result = parser.parse("(def bubblesort (x) (for i from 0 to (length x) do (for j from 0 to (length x) do (if (> (at x j) (at x (+ j 1))) ((defvar pom (at x j)) (set x j (at x (+ j 1))) (set x (+ j 1) pom)) x))))")->eval(mainEnvironment);
    result = parser.parse("(bubblesort (list 21 5 85 21 5632 5 22 1 11 1))")->eval(mainEnvironment);
    cout << result->toString() << endl;
    CPPUNIT_ASSERT(result->toString().compare("(1 1 5 5 11 21 21 22 85 5632)") == 0);
}
