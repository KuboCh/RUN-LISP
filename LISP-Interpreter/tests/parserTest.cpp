/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   parserTest.cpp
 * Author: phil
 *
 * Created on 27.1.2017, 9:33:49
 */

#include "../Parser.h"
#include "../Enviroment.h"
#include "../DataType.h"
#include <cppunit/extensions/HelperMacros.h>



class parserTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(parserTest);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    parserTest(){}
    virtual ~parserTest(){}
    void setUp(){}
    void tearDown(){}

private:
};



