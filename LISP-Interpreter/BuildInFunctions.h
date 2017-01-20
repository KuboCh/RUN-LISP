#include "Function.h"
#include "Enviroment.h"
#include "Nil.h"
#include "Number.h"
#include "String.h"

#ifndef BUILDINFUNCTIONS_H
#define BUILDINFUNCTIONS_H

class BuildInPlus : public Function {
private:
    DataType* sumNubers(Enviroment *e);
    DataType* sumStrings(Enviroment *e);
public:
    BuildInPlus();
    virtual ~BuildInPlus();
    virtual DataType* eval(Enviroment *e);
    virtual bool checkArgCount(int givenArgCount);
};

class BuildInDefvar : public Function {
public:
    BuildInDefvar();;
    virtual ~BuildInDefvar() {};
    DataType* eval(Enviroment *e);
    virtual bool checkArgCount(int givenArgCount);
};

class BuildInMinus : public Function {
public:
    BuildInMinus();;
    virtual ~BuildInMinus() {};
    DataType* eval(Enviroment *e);
    virtual bool checkArgCount(int givenArgCount);
};

class BuildInMultiplication : public Function {
public:
    BuildInMultiplication();;
    virtual ~BuildInMultiplication() {};
    DataType* eval(Enviroment *e);
    virtual bool checkArgCount(int givenArgCount);
};

class BuildInDefconst : public Function {
public:
    BuildInDefconst();;
    virtual ~BuildInDefconst() {};
    DataType* eval(Enviroment *e);
    virtual bool checkArgCount(int givenArgCount);
};

class BuildInList : public Function {
public:
    BuildInList();;
    virtual ~BuildInList() {};
    DataType* eval(Enviroment *e);
    virtual bool checkArgCount(int givenArgCount);
};

#endif /* BUILDINFUNCTIONS_H */

