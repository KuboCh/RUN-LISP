#include "Parser2Tests.h"


CPPUNIT_TEST_SUITE_REGISTRATION(Parser2Tests);

Parser2Tests::Parser2Tests() {
}

Parser2Tests::~Parser2Tests() {
}

void Parser2Tests::setUp() {
}

void Parser2Tests::tearDown() {
}

void Parser2Tests::testParenthesisCheck() {
    CPPUNIT_ASSERT(parser.parenthesisCheck("(hello (world))") == 0);
    CPPUNIT_ASSERT(parser.parenthesisCheck("(hello ((world !) (hello!)))") == 0);
    CPPUNIT_ASSERT(parser.parenthesisCheck("(hello ((world") == 3);
    CPPUNIT_ASSERT(parser.parenthesisCheck("(hello ((world)!)") == 1);
    try {
        parser.parenthesisCheck("(hello ((world)!)))))"); // more closing par.
        CPPUNIT_ASSERT(false); // should throw error
    } catch (const char* error) {
        CPPUNIT_ASSERT(true);
    }
}

void setCin(string s) {
    for (int i = s.size() - 1; i >= 0; i--)
        cin.putback(s[i]);
}

void Parser2Tests::testGetFullInput() {
    input = "(hello world)";
    CPPUNIT_ASSERT(parser.getFullInput(input) == "(hello world)");

    input = "(hello ";
    setCin("world)\n");
    CPPUNIT_ASSERT(parser.getFullInput(input) == "(hello world)");

    input = "(hello (world) (hello (hello ";
    setCin("world)\n world)\n world)\n");
    CPPUNIT_ASSERT(parser.getFullInput(input) == "(hello (world) (hello (hello world) world) world)");
}

void Parser2Tests::testTokenize() {
    list<string> output = parser.tokenize("(hello (world))");
    list<string> desired;
    desired.push_back("(");
    desired.push_back("hello");
    desired.push_back("(");
    desired.push_back("world");
    desired.push_back(")");
    desired.push_back(")");
    while(!output.empty()){
        if((*output.begin()).compare((*desired.begin())) != 0){
            CPPUNIT_ASSERT(false);
            break;
        }
        output.pop_front();
        desired.pop_front();
    }
    CPPUNIT_ASSERT(true);
}

