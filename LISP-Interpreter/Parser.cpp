#include <stdlib.h>
#include <algorithm>    // std::reverse
#include <limits>
#include "Parser.h"
#include "Enviroment.h"
#include "Error.h"
#include "Function.h"
#include "Void.h"
#include "Parametr.h"

using namespace std;

Parser::Parser() {
    talkToMe = false;
}

Parser::Parser(bool talk) {
    talkToMe = talk;
}

Parser::~Parser() {
}

// Push back string s to (standard) input stream

void Parser::pushBack(string s) {
    for (int i = s.size() - 1; i >= 0; i--)
        cin.putback(s[i]);
}

void skipWhiteSpaces() {
    while (cin.peek() == ' ' || cin.peek() == '\t' || cin.peek() == '\n') {
        cin.get();
    }
}

DataType* Parser::readString(string word) {
    string fullString = word;
    while (fullString.find('"', 1) == -1) { // if closing " was not found
        cin >> word;
        if (!word.empty())
            fullString += " " + word;
        else // input is empty and string was not ended by "
            return new Error("E: Error occured while reading string " + fullString + " - End of input.");

    }
    int pos = fullString.find('"', 1);
    word = fullString;
    if (pos + 1 != fullString.size()) { // there's something after " in string
        word.erase(0, pos + 1);
        pushBack(word);
    };
    return new String(fullString.substr(1, pos - 1));
}

DataType* Parser::readList(string word, Enviroment *e) {
    if (talkToMe)
        cout << "reading list" << endl;
    string element;
    List *list = new List();
    if (word == "(list") {
        cin >> element;
    } else {
        element = word.substr(1);
    }
    while (true) {
        if (element[0] == ')') {
            if (element.length() != 1) {
                element = element.substr(1);
                pushBack(element);
            }
            return list;
        }
        DataType *newElement = parse(element, e);
        if (newElement->dataType() == DataType::TYPE_ERROR) {
            return newElement;
        }
        list->addElement(newElement);
        cin >> element;
    }
}

// Read a number from input stream (actually: integers only)

DataType* Parser::readNumber(string word) {
    // check each char of word and create number
    string myWord = word;
    for (int i = 0; i < word.size(); i++) {
        if ((word[i] < '0') || (word[i] > '9')) { // NaN
            if (talkToMe)
                cout << "W: You've probably made a mistake in command " << word << ", but I will separate the number from it." << endl;
            myWord = word.substr(0, i);
            word.erase(0, i);
            pushBack(word);
            //            cout << "Pushing back word: \"" << word << "\"" << endl;
            break;
        }
    }
    return new Number(atoi(myWord.c_str()));
}

DataType* Parser::readSymbol(string word, Enviroment *e) {
    if (word.compare("true") == 0)
        return new True();
    else if (word.compare("false") == 0)
        return new False();
    else if (word.compare("nil") == 0)
        return new Nil();
    if (talkToMe)
        cout << "reading symbol" << endl;
    int pos = word.find_first_of("()");
    if (pos != -1) {
        pushBack(word.substr(pos));
        word = word.substr(0, pos);
    }
    Variable *var = e->getVariable(word);
    if (var == NULL) {
        return new Error("Variable " + word + " not found");
    }
    return var;
}

// nacita definovanie premennej, meno + hodnota, constant = ci je premenna konstanta

DataType* Parser::readVariable(bool constant, Enviroment *e) {
    string name;
    string word;
    cin >> name;
    cin >> word;
    DataType* value = parse(word, e);
    cin >> word;
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == ')') {
            if (i + 1 != word.length())
                pushBack(word.substr(i));
            break;
        }
        if (!(word[i] == ' ' || word[i] == '\t'))
            return new Error("Unexpected '" + word + "' in reading variable " + name);
    }
    return e->addVariable(name, value, constant);
}

// Read 1 inBodyFunction with params

pair<Function*, list<Parametr*> > Parser::readInBodyFunction(Enviroment* e, Function *function, int *varCount) {
    string arg;
    char bracket;
    cin >> bracket; // opening bracket (
    cin >> arg; // function name
    Function *functionInBody = e->getFunction(arg);
    if (functionInBody == NULL)
        throw "Function " + arg + " not declared";
    list<Parametr*> parameters;
    while (cin.peek() != ')') {
        (*varCount)++;
        cin >> arg;
        if (arg[0] == '(') { // param is a function
            pushBack(arg);
            int vCount = 0;
            pair<Function*, list<Parametr*> > ribf = readInBodyFunction(e, functionInBody, &vCount);
            Parametr * p = new Parametr();
            p->function = ribf.first;
            parameters.push_back(p);
        } else {
            int bpos = arg.find(')');
            if (bpos != -1) {
                pushBack(arg.substr(bpos));
                arg = arg.substr(0, bpos);
            }
            Parametr* p = new Parametr();
            if ((arg[0] >= '0') && (arg[0] <= '9')) {
                // je to cislo
                p->value = readNumber(arg);
                if (p->value->dataType() == DataType::TYPE_ERROR) {
                    cin.sync(); // clear the input buffer ??
                    throw p->value->toString(); //return p->value;
                }
            } else if (arg[0] == '"') {
                p->value = readString(arg);
                if (p->value->dataType() == DataType::TYPE_ERROR) {
                    cin.sync(); // clear the input buffer ??
                    throw p->value->toString(); //return p->value;
                }
            } else {
                if ((functionInBody->name == "defvar" || functionInBody->name == "defconst") && parameters.size() == 0) {
                    // pri defvar a defconst sa prvy parameter zameni za DataType String s value = nazov premennej
                    // inak by sa pri eval funkcii volal eval parametra - hladala by sa hodnota pre parameter, ktory sa ma este len vytvorit
                    p->value = new String(arg);
                } else {
                    p->parametrName = arg;
                }
            }
            parameters.push_back(p);
        }
    }
    cin.get(); // zoberie iba ), pre pripad ze je nieco za
    return pair<Function*, list<Parametr*> >(functionInBody, parameters);
}

// (def func (x y) (+ x y))

DataType* Parser::readFunction(Enviroment* e) {
    Function *function = new Function();
    cin >> function->name;
    if (e->getFunction(function->name))
        return new Error("Function " + function->name + " is already defined.");

    // Read arg list
    string arg;
    char bracket;
    cin >> bracket >> arg;
    int pos = arg.find(')');
    while (pos == -1) {
        function->addArgument(arg);
        cin >> arg;
        pos = arg.find(')');
    }
    // parse last argument
    if (pos != 0) // arg == blahblah)
        function->addArgument(arg.substr(0, pos)); 
    if (pos + 1 != arg.size()) // push back the rest of string
        pushBack(arg.erase(0, pos + 1));

    // Now parse functions in body!
    int varCount;
    skipWhiteSpaces();
    while (cin.peek() != ')') { // while end of list of functions: read one of them
        pair<Function*, list<Parametr*> > ribf;
        try {
            ribf = readInBodyFunction(e, function, &varCount);
        } catch (const char* error) {
            return new Error(error);
        }
        function->addToBody(ribf);
        skipWhiteSpaces();
    }
    cin >> bracket;
    e->addFunction(function);
    cout << function->name;
    return new Void();
}

DataType* Parser::readFunctionCall(string functionName, Enviroment *e) {
    int pos = functionName.find(")");
    bool hasParametrs = true;
    if (pos != -1) {
        //volanie funkcie bez parametrov
        hasParametrs = false;
        if (pos + 1 != functionName.size()) {
            pushBack(functionName.substr(pos + 1));
        }
        functionName = functionName.substr(0, pos);
    }
    Function *function = e->getFunction(functionName);
    if (function == NULL)
        return new Error("Call to undefined function " + functionName);
    Enviroment *functionEnviroment = new Enviroment();
    if (hasParametrs) {
        string var;
        cin >> var;
        pos = var.find(")");
        int i = 0;
        while (pos != 0) {
            DataType* nextParametr = parse(var, e);
            if (nextParametr->dataType() == DataType::TYPE_ERROR) {
                return nextParametr;
            }
            if (nextParametr->dataType() == DataType::TYPE_PARAMETR) {
                nextParametr = ((Variable*) nextParametr)->value;
            }
            try {
                functionEnviroment->addVariable(function->getParametrNameAt(i), nextParametr, false);
            } catch (const char* error) {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return new Error(error);
            }
            cin >> var;
            pos = var.find(")");
            if (pos != -1) { // najdena )
                if (var.length() != 1) { // nieco je pred alebo za )
                    string toPush = var.substr(pos);
                    var = var.substr(0, pos);
                    if (var == "") {
                        toPush = toPush.substr(1);
                        pushBack(toPush);
                        break;
                    }
                    pushBack(toPush);
                    pos = -1;
                }

            }
            i++;
        }
    }
    return function->eval(functionEnviroment);
}

/*
 * Parse content of the line as:
 * 1. Atom (Number, String, etc.)
 * 2. Symbol -> could be evaluated as atom/another symbol/list
 * 3. List -> functions/atoms/symbols/...
 */
DataType* Parser::parse(string word, Enviroment *e) {
    switch (word[0]) {
        case '"':
            return readString(word);
        case '(':
            if (word == "(defconst") {
                return readVariable(true, e);
            } else if (word == "(defvar") {
                return readVariable(false, e);
            } else if (word == "(def") {
                return readFunction(e);
            } else if (word == "(list") {
                return readList(word, e);
            } else {
                return readFunctionCall(word.substr(1), e); // calling a function
            }
        default:
            if (word[0] >= '0' && word[0] <= '9') {
                return readNumber(word);
            } else {
                return readSymbol(word, e); // symbol/function/true-false-nil
            }
            break;
    }
    return new Error("Undefined command");
}


