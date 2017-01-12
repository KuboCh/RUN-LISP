#include <string>
#include "Parametr.h"
#include <list>
#include <vector>
#include "DataType.h"
#include "Enviroment.h"

#ifndef FUNCTION_H
#define FUNCTION_H

using namespace std;

class Function {
public:
    Function();
    //Function(string name, int argCount, Parametr* args, List body);
    Function(const Function& orig);
    virtual ~Function();
    int getArgCount();
    void print();
    string name;
    vector<Parametr> args;
    list<Function*> body;
    int argCount;
    void addParametr(string name);
    void addToBody(Function *function);
    virtual DataType* eval(Enviroment *e);
private:
    
};

#endif /* FUNCTION_H */

