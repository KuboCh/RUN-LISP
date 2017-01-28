#ifndef PARSER2TESTS_H
#define PARSER2TESTS_H
#include <string>
#include <vector>
#include "../Parser2.h"

using namespace std;

#include <cppunit/extensions/HelperMacros.h>

class Parser2Tests : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(Parser2Tests);

    CPPUNIT_TEST(testParenthesisCheck);
    CPPUNIT_TEST(testGetFullInput);
    CPPUNIT_TEST(testTokenize);

    CPPUNIT_TEST_SUITE_END();

public:
    Parser2Tests();
    virtual ~Parser2Tests();
    void setUp();
    void tearDown();

private:
    void testParenthesisCheck();
    void testGetFullInput();
    void testTokenize();
    Parser2 parser;
    string input;
};

#endif /* PARSER2TESTS_H */

