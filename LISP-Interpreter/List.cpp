#include "List.h"

List::List() {
}

List::List(const List& orig) {
}

List::~List() {
}

void List::eval() {
    //TODO
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
