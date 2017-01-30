#include <string>
#include <list>
#include <vector>
#include "DataType.h"

using namespace std;

#ifndef FUNCTION_H
#define FUNCTION_H
class Parameter;
class Environment;

class Function : public DataType {
public:
    Function();
    Function(Environment * e);
    Function(const Function& orig);
    Function(const string& name);
    virtual ~Function();
    void addArgument(string name);
    void addToBody(pair<Function*, list<Parameter*> > ribf);
    
    virtual DataType* eval(Environment &e);
    virtual bool checkArgCount(int givenArgCount);
    DataType* evalFunctionInBody(list<pair<Function*, list<Parameter*> > >::iterator functionData);
    virtual string getParameterNameAt(int position);
    
    virtual int dataType() {
        return TYPE_FUNCTION;
    }
    
    virtual void print(){
        cout << name << endl;
    }

    virtual string toString() {
        return name;
    }
    
    string name;
    vector<string> argsNames;
    list<pair<Function*, list<Parameter*> > > body;
    Environment *functionEnvironment;
private:
    
};

#endif /* FUNCTION_H */

