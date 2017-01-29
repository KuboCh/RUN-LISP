#include <string>
#include "DataType.h"

using namespace std;

#ifndef ERROR_H
#define ERROR_H

class Error : public DataType {
public:
    Error();
    Error(string errorMessage);
    Error(const Error& orig);
    virtual ~Error();
     virtual DataType* eval(Enviroment& e);
    virtual void print();
    string errorMessage;
    int dataType() { return TYPE_ERROR; }
    virtual string toString();
private:

};

#endif /* ERROR_H */

