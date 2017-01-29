#include <string>

using namespace std;

#ifndef PARAMETR_H
#define PARAMETR_H
class Function;
class DataType;
class Enviroment;

class Parametr {
public:
    static const int TYPE_FUNCTION = 1;
    static const int TYPE_DATA_VALUE = 2;
    static const int TYPE_VARIABLE_NAME = 3;
    Parametr();
    Parametr(const Parametr& orig);
    virtual ~Parametr();
    Function *function;
    DataType *value;
    string parametrName = "";
    DataType* eval(Enviroment *e);
    int getType();
private:

};

#endif /* PARAMETR_H */

