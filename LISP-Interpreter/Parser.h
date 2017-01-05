#include <string>

#ifndef PARSER_H
#define PARSER_H

using namespace std;

class Parser {
public:
    Parser();
    Parser(const Parser& orig);
    virtual ~Parser();
    void parse(string line);
private:

};


#endif /* PARSER_H */

