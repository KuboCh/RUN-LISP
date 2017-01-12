#include<vector>
#include<map>
#include "Parametr.h"
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
    static const string variableNames[];
    Enviroment();
    Enviroment(const Enviroment& orig);
    virtual ~Enviroment();
    Parametr* getParametr(string name);
    DataType* addParametr(string name, DataType* value, bool isConstant);
    void removeParametr(Parametr *parametr);
    Function* addFunction(Function *function);
    Function* getFunction(string name, Parametr *arg);
    Function* getFunction(string name);
    void removeFunction(Function function);
    map<string, Parametr*>::const_iterator getParametrsIterator();
    map<string, Parametr*>::const_iterator getParametrsIteratorEnd();
    int getNumberOfParametrs();
private:
    map<string, Parametr*> parametrs;
    vector<Function*> functions;
    int numberOfParametrs;
};

#endif /* ENVIROMENT_H */

