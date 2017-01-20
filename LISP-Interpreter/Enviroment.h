#include<vector>
#include<map>
#include "Variable.h"
#include "List.h"


#ifndef ENVIROMENT_H
#define ENVIROMENT_H

class Function;
using namespace std;

class Enviroment {
public:
    //TODO vymysliet lepsi sposob?
    static const string varNameAt(int index) {
        const string variableNames[] = {"1var", "2var", "3var", "4var", "5var", "6var", "7var", "8var", "9var"};
        return variableNames[index];
  } 
    Enviroment();
    Enviroment(const Enviroment& orig);
    virtual ~Enviroment();
    Variable* getVariable(string name);
    DataType* addVariable(string name, DataType* value, bool isConstant);
    void removeVariable(Variable *parametr);
    Function* addFunction(Function *function);
    Function* getFunction(string name, Variable *arg);
    Function* getFunction(string name);
    void removeFunction(Function function);
    map<string, Variable*>::const_iterator getParametrsIterator();
    map<string, Variable*>::const_iterator getParametrsIteratorEnd();
    int getNumberOfVariables();
private:
    map<string, Variable*> variables;
    vector<Function*> functions;
    int numberOfVariables;
};

#endif /* ENVIROMENT_H */

