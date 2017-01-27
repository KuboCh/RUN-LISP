/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ParserTest.h
 * Author: phil
 *
 * Created on 27.1.2017, 9:47:03
 */

#ifndef PARSERTEST_H
#define PARSERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../Parser.h"
#include "../Enviroment.h"
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
    Enviroment e;
    void testBasicDataTypes();
    void testBasicVariables();
    void testBasicVariablesWithSpace();
    void testBasicLists();
    void testBasicFunctions();
};

#endif /* PARSERTEST_H */

