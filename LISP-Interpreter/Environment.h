#include <vector>
#include <map>
#include <sstream>

using namespace std;

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
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
    bool removeVariable(string name);
    
    Function* addFunction(Function *function);
    Function* getFunction(string name, Variable *arg);
    Function* getFunction(string name);
    bool removeFunction(string name);
    
    map<string, Variable*>::iterator getParametersIterator();
    map<string, Variable*>::iterator getParametersIteratorEnd();
    int getNumberOfVariables();
    void print();
    
    static const string varNameAt(int index) {
        //        const string variableNames[] = {"1var", "2var", "3var", "4var", "5var", "6var", "7var", "8var", "9var"};
        //        return variableNames[index];
        return static_cast<ostringstream*> (&(ostringstream() << index))->str() + "var";
    }
    bool mark;
    
    /*
     * Empty all for next use
     */
    void empty(){
        variables.clear();
        functions.clear();
        numberOfVariables = 0;
    }
private:
    map<string, Variable*> variables;
    vector<Function*> functions;
    int numberOfVariables;
};

#endif /* ENVIRONMENT_H */

