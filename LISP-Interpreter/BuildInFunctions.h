#include <string>
#include "Function.h"

using namespace std;

#ifndef BUILDINFUNCTIONS_H
#define BUILDINFUNCTIONS_H
class DataType;
class Environment;

class BuildInPlus : public Function {
private:
    DataType* sumNubers(Environment &e);
    DataType* sumStrings(Environment &e);
public:
    BuildInPlus();
    virtual ~BuildInPlus();
    virtual DataType* eval(Environment &e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInDefvar : public Function {
public:
    BuildInDefvar();;
    virtual ~BuildInDefvar() {};
    virtual DataType* eval(Environment &e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInMinus : public Function {
public:
    BuildInMinus();;
    virtual ~BuildInMinus() {};
    virtual DataType* eval(Environment &e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInMultiplication : public Function {
public:
    BuildInMultiplication();;
    virtual ~BuildInMultiplication() {};
    virtual DataType* eval(Environment &e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInDefconst : public Function {
public:
    BuildInDefconst();;
    virtual ~BuildInDefconst() {};
    virtual DataType* eval(Environment &e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInList : public Function {
public:
    BuildInList();;
    virtual ~BuildInList() {};
    virtual DataType* eval(Environment &e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

// ==
class BuildInEqual : public Function {
public:
    BuildInEqual();;
    virtual ~BuildInEqual() {};
    virtual DataType* eval(Environment &e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

//// <
//class BuildInLower : public Function {
//public:
//    BuildInLower();;
//    virtual ~BuildInLower() {};
//    virtual DataType* eval(Environment &e);
//    virtual bool checkArgCount(int givenArgCount);
//    virtual string getParameterNameAt(int position);
//};
//
//// >
//class BuildInGreater : public Function {
//public:
//    BuildInGreater();;
//    virtual ~BuildInGreater() {};
//    virtual DataType* eval(Environment &e);
//    virtual bool checkArgCount(int givenArgCount);
//    virtual string getParameterNameAt(int position);
//};
//
//// <=
//class BuildInLeq : public Function {
//public:
//    BuildInLeq();;
//    virtual ~BuildInLeq() {};
//    virtual DataType* eval(Environment &e);
//    virtual bool checkArgCount(int givenArgCount);
//    virtual string getParameterNameAt(int position);
//};
//
//// >=
//class BuildInGeq : public Function {
//public:
//    BuildInGeq();;
//    virtual ~BuildInGeq() {};
//    virtual DataType* eval(Environment &e);
//    virtual bool checkArgCount(int givenArgCount);
//    virtual string getParameterNameAt(int position);
//};

#endif /* BUILDINFUNCTIONS_H */

