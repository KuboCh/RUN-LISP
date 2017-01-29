#include <string>
#include <list>
#include <vector>

using namespace std;

#ifndef FUNCTION_H
#define FUNCTION_H
class Parametr;
class DataType;
class Enviroment;

class Function {
public:
    Function();
    Function(Enviroment * e);
    //Function(string name, int argCount, Parametr* args, List body);
    Function(const Function& orig);
    virtual ~Function();
    //int getArgCount();
    void print();
    void addArgument(string name);
    void addToBody(pair<Function*, list<Parametr*> > ribf);
    virtual DataType* eval(Enviroment *e);
    virtual bool checkArgCount(int givenArgCount);
    DataType* evalFunctionInBody(list<pair<Function*, list<Parametr*> > >::iterator functionData);
    virtual string getParametrNameAt(int position);
    void printFunctionParams();
    
    string name;
    vector<string> argsNames;
    list<pair<Function*, list<Parametr*> > > body;
    int argCount;
    Enviroment *functionEnviroment;
private:
    
};

#endif /* FUNCTION_H */

