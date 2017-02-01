#include <string>
#include "../LispStack.h"
#include "../Memory.h"
#include "../Environment.h"
#include "../Function.h"
#include "../Parser.h"


using namespace std;

#ifndef EVALTESTS_H
#define EVALTESTS_H

#include <cppunit/extensions/HelperMacros.h>

class EvalTests : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(EvalTests);

    CPPUNIT_TEST(testAtomEval);
    CPPUNIT_TEST(testVariables);
    CPPUNIT_TEST(testFunctions);
    CPPUNIT_TEST(testIf);
    CPPUNIT_TEST(testFor);

    CPPUNIT_TEST_SUITE_END();

public:
    EvalTests();
    virtual ~EvalTests();
    void setUp();
    void tearDown();

private:

    void testAtomEval();
    void testVariables();
    void testFunctions();
    void testIf();
    void testFor();
    Parser parser;
    DataType* result;
    string input;
    Environment *mainEnvironment;
    Function *mainFunction;
};

#endif /* EVALTESTS_H */

