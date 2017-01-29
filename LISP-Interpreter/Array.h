#include <vector>
#include <iostream>
#include <string>
#include "Enviroment.h"

using namespace std;

#ifndef ARRAY_H
#define ARRAY_H
class DataType;

class Array {
public:
    vector<Array*> a;
    Array();
    Array(const Array& orig);
    virtual ~Array();

    virtual string toString() {
        string s = "[";
        for (int i = 0; i != a.size(); i++) {
            s += a[i]->toString();
        }
        s += "]";
        return s;
    }

    bool isAtom() {
        return a.size() == 0;
    }

    virtual DataType* eval(Enviroment& e) {
        if (a.size() > 0) {
            if (a[0]->toString().compare("defvar") == 0) {
                if (a.size() == 3) {
                    return e.addVariable(a[1]->toString(), a[2]->eval(e), false); // TODO bude fungovat pre zlozitejsie (defvar x (+ x 5)) ??
                } else {
                    cout << "(defvar name value)" << endl;
                }

            } else if (a[0]->toString().compare("defconst") == 0) {
                if (a.size() == 3) {
                    return e.addVariable(a[1]->toString(), a[2]->eval(e), true); // TODO bude fungovat pre zlozitejsie (defvar x (+ x 5)) ??
                } else {
                    cout << "(defconst name value)" << endl;
                }
            } else if (a[0]->toString().compare("def") == 0) { // TODO define function
                cout << "Define function " << a[1]->toString() << endl;
            } else { // ToDo call function
                cout << "Call function " << a[0]->toString() << endl;
            }
        }
        cout << "Abstract Array eval() should be overriden." << endl;
        return NULL;
    }
private:
};

#endif /* ARRAY_H */

