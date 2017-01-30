#include <string>

using namespace std;

#ifndef PARAMETER_H
#define PARAMETER_H
class Function;
class DataType;
class Environment;
class Array;

class Parameter {
public:
    Parameter();
    Parameter(const Parameter& orig);
    virtual ~Parameter();
    Function *function;
    Array *value;
    string parameterName = "";
    DataType* eval(Environment *e);
private:

};

#endif /* PARAMETER_H */

