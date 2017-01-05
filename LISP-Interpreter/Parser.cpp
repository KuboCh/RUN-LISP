#include <stdlib.h>
#include <algorithm>    // std::reverse

#include "Parser.h"

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

String Parser::readString(string word) {
    string myWord = word;
    int p = myWord.find('"', 1);
    while (p == -1) { // ending " was not found, read another word and try again
        cin >> word;
        if (!word.empty()) {
            myWord += " ";
            myWord += word;
        } else { // input is empty and string was not ended by "
            cout << "E: Error occured while reading string.";
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
    return String(myWord);
}

void Parser::readList(string word) {
    if (talkToMe)
        cout << "You should learn me to read lists." << endl;
}

Number Parser::readNumber(string word) {
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
    return Number(atoi(myWord.c_str()));
}

DataType* Parser::readSymbol(string word) {
    if (talkToMe)
        cout << "You should learn me to read symbols." << endl;
    if (word == "true")
        return new True();
    else if (word == "false")
        return new False();
    else if (word == "nil")
        return new Nil();
    else {
        cout << "do something with symbol " << word << endl;
        return new DataType();
    }
}

/*
 * Parse content of the line as:
 * 1. Atom (Number, String, etc.)
 * 2. Symbol -> could be evaluated as atom/another symbol/list
 * 3. List -> functions/atoms/symbols/...
 */
void Parser::parse(string word) {
    switch (word[0]) {
        case '"':
            if (talkToMe)
                cout << "Parser: Hmm... It could be a string!" << endl;
            readString(word).print();
            break;
        case '(':
            if (talkToMe)
                cout << "Parser: Hmm... It could be a list!" << endl;
            readList(word);
            break;
        default:
            if (word[0] >= '0' && word[0] <= '9') {
                if (talkToMe)
                    cout << "Parser: Hmm... It could be a number!" << endl;
                readNumber(word).print();
            } else { // symbol/function/true-false-nil
                if (talkToMe)
                    cout << "Parser: Hmm... It could be a symbol!" << endl;
                readSymbol(word)->print();
            }
            break;
    }
}


