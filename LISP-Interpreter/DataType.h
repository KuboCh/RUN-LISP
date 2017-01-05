#include <string>
#include <iostream>

#ifndef DATATYPE_H
#define DATATYPE_H

using namespace std;

class DataType {
public:
    DataType();
    DataType(const DataType& orig);
    virtual ~DataType();
    void eval();
private:

};

#endif /* DATATYPE_H */

