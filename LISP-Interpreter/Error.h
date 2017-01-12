#include <string>

#include "DataType.h"

#ifndef ERROR_H
#define ERROR_H

using namespace std;

class Error : public DataType {
public:
    Error();
    Error(string errorMessage);
    Error(const Error& orig);
    virtual ~Error();
    void eval();
    virtual void print();
    string errorMessage;
    int dataType() { return TYPE_ERROR; }
    virtual string toString();
private:

};

#endif /* ERROR_H */

