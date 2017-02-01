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

    virtual DataType* eval(Environment* e);
    virtual void print();
    virtual string toString();

    int dataType() {
        return TYPE_ERROR;
    }

    string errorMessage;
private:

};

#endif /* ERROR_H */

