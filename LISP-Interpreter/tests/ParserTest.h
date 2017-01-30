#ifndef PARSERTEST_H
#define PARSERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../Parser.h"
#include "../Environment.h"
#include "../DataType.h"
#include "../BuildInFunctions.h"

class ParserTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ParserTest);

    CPPUNIT_TEST(testBasicDataTypes);
    CPPUNIT_TEST(testBasicVariables);
    CPPUNIT_TEST(testBasicVariablesWithSpace);
    CPPUNIT_TEST(testBasicLists);
    CPPUNIT_TEST(testBasicFunctions);

    CPPUNIT_TEST_SUITE_END();

public:
    ParserTest();
    virtual ~ParserTest();
    void setUp();
    void tearDown();

private:
    Parser p;
    Environment e;
    void testBasicDataTypes();
    void testBasicVariables();
    void testBasicVariablesWithSpace();
    void testBasicLists();
    void testBasicFunctions();
};

#endif /* PARSERTEST_H */

