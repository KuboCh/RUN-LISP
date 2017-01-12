#include <stdlib.h>
#include <algorithm>    // std::reverse
#include "Parser.h"
#include "Enviroment.h"
#include "Error.h"
#include "Function.h"

using namespace std;

void pushBack(string s) {
    for (int i = s.size() - 1; i >= 0; i--)
        cin.putback(s[i]);
}

Parser::Parser() {
    talkToMe = false;
}

Parser::Parser(bool talk) {
    talkToMe = talk;
}

Parser::~Parser() {
}

DataType* Parser::readString(string word) {
    //TODO prec apostrofy z value
    string myWord = word;
    int p = myWord.find('"', 1);
    while (p == -1) { // ending " was not found, read another word and try again
        cin >> word;
        if (!word.empty()) {
            myWord += " ";
            myWord += word;
        } else { // input is empty and string was not ended by "
            cout << "E: Error occured while reading string.";
            return new Nil();
        }
        p = myWord.find('"', 1);
    }
    // You have the full string, check what's after it
    word = myWord;
    if (p + 1 != word.size()) {
        if (talkToMe)
            cout << "W: You've probably made a mistake in command " << word << ", but I will separate the string from it." << endl;
        word.erase(0, p + 1);
        myWord = myWord.substr(0, p + 1);
        pushBack(word);
        //        cout << "Pushing back word: \"" << word << "\"" << endl;
    }
    return new String(myWord);
}

DataType* Parser::readList(string word, Enviroment *e) {
    if (talkToMe)
        cout << "You should learn me to read lists." << endl;
    string element;
    List *list = new List();
    if (word == "(list") {
        cin >> element;
    } else {
        element = word.substr(1);
    }
    while (true) {
        if (element[0] == ')') {
            if (element.length() != 1){
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
    if (word == "true")
        return new True();
    else if (word == "false")
        return new False();
    else if (word == "nil")
        return new Nil();
    else {
        if (talkToMe)
            cout << "You should learn me to read symbols." << endl;
        int pos = word.find_first_of("()");
            if (pos != -1){
                pushBack(word.substr(pos));
                word = word.substr(0, pos);
            }
        Parametr *var = e->getParametr(word);
        if (var == NULL){   
            return new Error("Variable " + word + " not found");
        } else {
            return var;
        }
        //return new DataType();
    }
}

DataType* Parser::readParametr(bool constant, Enviroment *e) {
    string name;
    DataType* value;
    cin >> name;
    string word;
    cin >> word;
    value = parse(word, e);
    cin >> word;
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == ')') {
            if (i + 1 != word.length()) {
                pushBack(word.substr(i));
            }
            break;
        }
        if (!(word[i] == ' ' || word[i] == '\t')) {
            return new Error("Unexpected '" + word + "' in reading variable " + name);
        }
    }
    return e->addParametr(name, value, constant);
}

DataType* Parser::readFunction(Enviroment* e) {
    Function *function = new Function();
    cin >> function->name;
    //TODO kontrola mena
    string var;
    cin >> var;
    int pos = var.find(")");
    while (pos == -1){
        function->addParametr(var);
        cin >> var;
        pos = var.find(")");
    }
    if (pos != 0) {
        function->addParametr(var.substr(0, pos));
    }
    var = var.substr(pos);
    if (var.length() == 0) {
        cin >> var;
    }
    while (var.length() != 0) {
        //TODO
        //function.addToBody()
    }
}

DataType* Parser::callFunction(string functionName, Enviroment *e) {
    Function *function = e->getFunction(functionName);
    if (function == NULL) {
        return new Error("Call to undefinde function " + functionName);
    }
    Enviroment *functionEnviroment = new Enviroment();
    string var;
    cin >> var;
    int pos = var.find(")");
    int i = 0;
    while (pos != 0) {
        DataType* nextParametr = parse(var, e);
        if (nextParametr->dataType() == DataType::TYPE_ERROR) {
            return nextParametr;
        }
        if (nextParametr->dataType() == DataType::TYPE_PARAMETR) {
            nextParametr = ((Parametr*) nextParametr)->value;
        }
        functionEnviroment->addParametr(Enviroment::varNameAt(i), nextParametr, false);
        cin >> var;
        pos = var.find(")");
        if (pos != -1) {
            if (pos != 0) {
                string toPush = var.substr(pos);
                var = var.substr(0, pos);
                pushBack(toPush);
                pos = -1;
            }
        }
        i++;
    }
    //TODO kontrola poctu parametrov alebo lepsie az v eval?
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
            if (talkToMe)
                cout << "Parser: Hmm... It could be a string!" << endl;
            return readString(word);
            break;
        case '(':
            if (talkToMe)
                cout << "Parser: Hmm... It could be a list!" << endl;
            if (word == "(defconst") {
                return readParametr(true, e);
            } else if (word == "(defvar") {
                return readParametr(false, e);
            } else if (word == "(def") {
                return readFunction(e);
            } else if (word == "(list") {
                return readList(word, e);
            } else { // 
                if (talkToMe)
                    cout << "Parser: Hmm... It could be call to function!" << endl;
                return callFunction(word.substr(1), e);
            }
            break;
        default:
            if (word[0] >= '0' && word[0] <= '9') {
                if (talkToMe)
                    cout << "Parser: Hmm... It could be a number!" << endl;
                return readNumber(word);
            } else { // symbol/function/true-false-nil
                if (talkToMe)
                    cout << "Parser: Hmm... It could be a symbol!" << endl;
                return readSymbol(word, e);
            }
            break;
    }
    return new Error("Undefined command");
}


