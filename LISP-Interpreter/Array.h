#include <vector>
#include <string>

using namespace std;

#ifndef ARRAY_H
#define ARRAY_H

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
    
    bool isAtom(){
        return a.size() == 0;
    }
private:
};

#endif /* ARRAY_H */

