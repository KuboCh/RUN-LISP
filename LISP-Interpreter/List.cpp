#include "List.h"

List::List() {
}

List::List(const List& orig) {
}

List::~List() {
}

DataType* List::eval(Environment& e) {
    return this;
}

void List::print(){
    cout << "(";
    for (list<DataType*>::const_iterator it = elements.begin(); it != elements.end(); ++it){
        if (it != elements.begin()) { 
            cout << " ";
        }
        (*it)->print();
    }
    cout << ")";
}

void List::addElement(DataType *element) {
    elements.push_back(element);
}

string List::toString() {
    string result = "(";
    for (list<DataType*>::const_iterator it = elements.begin(); it != elements.end(); ++it){
        if (it != elements.begin()) { 
            result += " ";
        }
        result += (*it)->toString();
    }
    result += ")";
    return result;
}
