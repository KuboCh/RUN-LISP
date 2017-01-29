#include <string>
#include "Function.h"

using namespace std;

#ifndef BUILDINFUNCTIONS_H
#define BUILDINFUNCTIONS_H
class DataType;
class Enviroment;
//class Function;

class BuildInPlus : public Function {
private:
    DataType* sumNubers(Enviroment *e);
    DataType* sumStrings(Enviroment *e);
public:
    BuildInPlus();
    virtual ~BuildInPlus();
    virtual DataType* eval(Enviroment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParametrNameAt(int position);
};

class BuildInDefvar : public Function {
public:
    BuildInDefvar();;
    virtual ~BuildInDefvar() {};
    DataType* eval(Enviroment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParametrNameAt(int position);
};

class BuildInMinus : public Function {
public:
    BuildInMinus();;
    virtual ~BuildInMinus() {};
    DataType* eval(Enviroment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParametrNameAt(int position);
};

class BuildInMultiplication : public Function {
public:
    BuildInMultiplication();;
    virtual ~BuildInMultiplication() {};
    DataType* eval(Enviroment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParametrNameAt(int position);
};

class BuildInDefconst : public Function {
public:
    BuildInDefconst();;
    virtual ~BuildInDefconst() {};
    DataType* eval(Enviroment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParametrNameAt(int position);
};

class BuildInList : public Function {
public:
    BuildInList();;
    virtual ~BuildInList() {};
    DataType* eval(Enviroment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParametrNameAt(int position);
};

#endif /* BUILDINFUNCTIONS_H */

