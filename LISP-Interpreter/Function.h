#include <string>
#include "Variable.h"
#include <list>
#include <vector>
#include "DataType.h"
#include "Enviroment.h"

#ifndef FUNCTION_H
#define FUNCTION_H

class Parametr;

using namespace std;

class Function {
public:
    Function();
    //Function(string name, int argCount, Parametr* args, List body);
    Function(const Function& orig);
    virtual ~Function();
    //int getArgCount();
    void print();
    string name;
    vector<string> argsNames;
    list<pair<Function*, list<Parametr*> > > body;
    int argCount;
    void addArgument(string name);
    void addToBody(Function *function, list<Parametr*> parametrs);
    virtual DataType* eval(Enviroment *e);
    Enviroment *functionEnviroment;
    virtual bool checkArgCount(int givenArgCount);
private:
    
};

#endif /* FUNCTION_H */

