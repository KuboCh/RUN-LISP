#include <vector>
#include <map>
#include <sstream>

using namespace std;

#ifndef ENVIROMENT_H
#define ENVIROMENT_H
class Variable;
class Function;
class DataType;

class Environment {
public:
    Environment();
    Environment(const Environment& orig);
    virtual ~Environment();
    
    Variable* getVariable(string name);
    DataType* addVariable(string name, DataType* value, bool isConstant);
//    void removeVariable(Variable *parameter);
    
    Function* addFunction(Function *function);
    Function* getFunction(string name, Variable *arg);
    Function* getFunction(string name);
//    void removeFunction(Function function);
    
    map<string, Variable*>::const_iterator getParametersIterator();
    map<string, Variable*>::const_iterator getParametersIteratorEnd();
    int getNumberOfVariables();
    void print();
    
    static const string varNameAt(int index) {
        //        const string variableNames[] = {"1var", "2var", "3var", "4var", "5var", "6var", "7var", "8var", "9var"};
        //        return variableNames[index];
        return static_cast<ostringstream*> (&(ostringstream() << index))->str() + "var";
    }
private:
    map<string, Variable*> variables;
    vector<Function*> functions;
    int numberOfVariables;
};

#endif /* ENVIROMENT_H */

