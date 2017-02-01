#include <string>
#include "Function.h"

using namespace std;

#ifndef BUILDINFUNCTIONS_H
#define BUILDINFUNCTIONS_H
class DataType;
class Environment;

class BuildInPlus : public Function {
private:
    DataType* sumNubers(Environment *e);
    DataType* sumStrings(Environment *e);
public:
    BuildInPlus();
    virtual ~BuildInPlus();
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInDefvar : public Function {
public:
    BuildInDefvar();;
    virtual ~BuildInDefvar() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInMinus : public Function {
public:
    BuildInMinus();;
    virtual ~BuildInMinus() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInMultiplication : public Function {
public:
    BuildInMultiplication();
    virtual ~BuildInMultiplication() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInDefconst : public Function {
public:
    BuildInDefconst();
    virtual ~BuildInDefconst() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInList : public Function {
public:
    BuildInList();
    virtual ~BuildInList() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

// ==
class BuildInEqual : public Function {
public:
    BuildInEqual();
    virtual ~BuildInEqual() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

// <
class BuildInLower : public Function {
public:
    BuildInLower();
    virtual ~BuildInLower() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

// >
class BuildInGreater : public Function {
public:
    BuildInGreater();
    virtual ~BuildInGreater() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

// &&
class BuildInAnd : public Function {
public:
    BuildInAnd();
    virtual ~BuildInAnd() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

// ||
class BuildInOr : public Function {
public:
    BuildInOr();
    virtual ~BuildInOr() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

// undef
class BuildInUndef : public Function {
public:
    BuildInUndef();
    virtual ~BuildInUndef() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInIf : public Function {
public:
    BuildInIf();;
    virtual ~BuildInIf() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInFor : public Function {
public:
    BuildInFor();;
    virtual ~BuildInFor() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInOut : public Function {
public:
    BuildInOut();;
    virtual ~BuildInOut() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInReturn : public Function {
public:
    BuildInReturn();;
    virtual ~BuildInReturn() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInAt : public Function {
public:
    BuildInAt();;
    virtual ~BuildInAt() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInSet : public Function {
public:
    BuildInSet();;
    virtual ~BuildInSet() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInDelete : public Function {
public:
    BuildInDelete();;
    virtual ~BuildInDelete() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInAdd : public Function {
public:
    BuildInAdd();;
    virtual ~BuildInAdd() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

class BuildInLength : public Function {
public:
    BuildInLength();
    virtual ~BuildInLength() {};
    virtual DataType* eval(Environment *e);
    virtual bool checkArgCount(int givenArgCount);
    virtual string getParameterNameAt(int position);
};

#endif /* BUILDINFUNCTIONS_H */

