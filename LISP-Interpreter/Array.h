#include <vector>
#include <list>
#include <iostream>
#include <string>

#include "Parameter.h"
#include "Environment.h"

using namespace std;

#ifndef ARRAY_H
#define ARRAY_H
class DataType;
class Environment;
class Parameter;
class Function;

class Array {
public:
    Array();
    Array(const Array& orig);
    virtual ~Array();
    virtual DataType* eval(Environment* e);
    DataType* defFunction(Environment* e);
    DataType* undefFunction(Environment* e);
    pair<Function*, list<Parameter*> > getInBodyFunction(Environment* e);
    pair<Function*, list<Parameter*> > getInBodyFor(Environment* e, Function* function);
    pair<Function*, list<Parameter*> > getInBodyIf(Environment *e, Function* function);
    Parameter* getParameter(Function *function, Environment *e, int position);
    DataType* callFunction(Environment* e);
    DataType* processIf(Environment* e);
    DataType* processLoop(Environment* e);
    virtual string toString();

    /*
     * Atom does not have body and it's functions are delegated to DataType's functions
     */
    bool isAtom() { 
        return a.size() == 0;
    }

    string operator[](int i) {
        return a.at(i)->toString();
    }
    
    vector<Array*> a;
private:
};

#endif /* ARRAY_H */

