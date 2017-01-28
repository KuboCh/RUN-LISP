#include "Parser2.h"

Parser2::Parser2() {
}

Parser2::Parser2(const Parser2& orig) {
}

Parser2::~Parser2() {
}

/*
 *  Check the count of parenthesis in the given text
 * @throws string If there are more closed then opened parenthesis (no way to repair it).
 */
int Parser2::parenthesisCheck(string text) {
    int openedParenthesis = 0;
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == '(') {
            openedParenthesis += 1;
            //cout << "Adding p from pos " << i << ", pcount = " << openedParenthesis << endl;
        } else if (text[i] == ')') {
            if (openedParenthesis > 0) {
                openedParenthesis -= 1;
                //cout << "Removing p from pos " << i << ", pcount = " << openedParenthesis << endl;
            } else
                throw "E: Parenthesis count is wrong.";
        }
    }
    return openedParenthesis;
}

/*
 *  Get all the parenthesis with content from input
 * @return string Full read input.
 */
string Parser2::getFullInput(string& line) {
    string wholeLine = line;
    while (this->parenthesisCheck(wholeLine) > 0) {
        getline(cin, line);
        wholeLine += line;
    }
    return wholeLine;
}

/*
 * @returns For input string "hello    \t \n" returns "hello"
 */
void removeEndingWhiteSpaces(string& s) {
    int endPos = s.size() - 1;
    while ((s[endPos] == ' ' || s[endPos] == '\t' || s[endPos] == '\n') && endPos != -1)
        endPos--;
    if (endPos != -1) {
        s = s.substr(0, endPos + 1);
    } else {
        s = "";
    }
}

/*
 * Get tokens from string input
 * @Param input Correct input (with correct parenthesis count).
 * @Example 
 * For input (hello (world)) it will return<br>
 * ["(", "hello", "(", "world", ")", ")"]
 * @return string array The array of tokens for input.
 */
list<string> Parser2::tokenize(const string input) {
    list<string> tokens;
    bool wordStarted = false;
    bool isString = false;
    string readWord;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '(' || input[i] == ')') {
            if (wordStarted && readWord.size() > 0) { // end reading
                removeEndingWhiteSpaces(readWord);
                tokens.push_back(readWord);
                readWord = "";
            }
            tokens.push_back(string(1, input[i])); // separate parenthesis
            wordStarted = false;
        } else {
            if (wordStarted) { // continue reading word
                if (!isString && (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')) {
                    removeEndingWhiteSpaces(readWord);
                    tokens.push_back(readWord);
                    readWord = "";
                } else {
                    readWord += input[i];
                }
            } else { // jump the leading spaces and start to read word
                if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
                    continue;
                if (input[i] == '"')
                    isString = true;
                wordStarted = true;
                readWord += input[i];
            }
        }
    }
    if (readWord != "") {
        tokens.push_back(readWord);
    }
    return tokens;
}

/*
 * Check each char of word and create number.
 */
Number* readNumber(const string& word) {
    for (int i = 0; i < word.size(); i++) {
        if ((word[i] < '0') || (word[i] > '9')) {
            throw "E: Cannot create number from token " + word;
        }
    }
    return new Number(atoi(word.c_str()));
}

Symbol* readSymbol(string name, Enviroment& e) {
    if (name.compare("true") == 0)
        return new True();
    else if (name.compare("false") == 0)
        return new False();
    else if (name.compare("nil") == 0)
        return new Nil();
    return new Symbol(name);
}

/*
 * Easier way to compare 2 string.
 */
bool is(const string& first, const string& second) {
    return first.compare(second) == 0;
}

/*
 * Take separated tokens and give them some meaning:
 * 1. Atom (Number, String, etc.)
 * 2. Symbol -> could be evaluated as atom/another symbol/list
 * 3. List -> functions/atoms/symbols/...
 */
Array* giveMeaningToTokens(list<string>& tokens, Enviroment& e) {
    Array* result = new Array();
    string token;
    if (tokens.size() == 0)
        throw "Token count is too small to evaluate it.";
    token = (*tokens.begin());
    tokens.pop_front();
    if (is(token, "(")) { // List (basic/function/if/...)
        Array* partial = new Array();
        while (!is((*tokens.begin()), ")")) {
            partial->a.push_back(giveMeaningToTokens(tokens, e));
        }
        tokens.pop_front(); // )
        return partial;
    } else if (is(token, ")")) {
        throw "Unexpected ) in token list.";
    } else { // Atoms/Symbols
        if (token[0] == '"') {
            //            result->a.push_back(new String(token));
            //            return result;
            return new String(token);
        } else if (token[0] >= '0' && token[0] <= '9') {
            //            result->a.push_back(readNumber(token));
            //            return result;
            return readNumber(token);
        } else {
            //            result->a.push_back(readSymbol(token, e));
            //            return result;
            return readSymbol(token, e);
        }
    }
    return result;
}

/*
 * Parse content
 */
Array* Parser2::parse(string line, Enviroment& e) {
    string input;
    Array *result;
    try {
        input = getFullInput(line);
        list<string> tokens = tokenize(input);
        result = giveMeaningToTokens(tokens, e);
    } catch (const char* error) {
        cout << error << endl;
        cin.sync(); // clear the input buffer ??
        cout << "Try to enter your commands again." << endl;
    }
    return result;
}
