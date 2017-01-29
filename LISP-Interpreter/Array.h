#include <vector>
#include <list>
#include <iostream>
#include <string>

using namespace std;

#ifndef ARRAY_H
#define ARRAY_H
class DataType;
class Enviroment;
class Parametr;
class Function;

class Array {
public:
    vector<Array*> a;
    Array();
    Array(const Array& orig);
    virtual ~Array();

    virtual string toString();

    bool isAtom() {
        return a.size() == 0;
    }

    virtual DataType* eval(Enviroment& e);
    DataType* defFunction(Enviroment& e);
    pair<Function*, list<Parametr*> > getInBodyFunction(Enviroment& e);
    DataType* callFunction(Enviroment& e);

    string operator[](int i) {
        return a.at(i)->toString();
    }
private:
};

#endif /* ARRAY_H */

