#include "List.h"

List::List() {
}

List::List(const List& orig) {
}

List::~List() {
}

DataType* List::eval(Environment* e) {
//    List *l = new List();
//    for (vector<Array*>::const_iterator it = elements.begin(); it != elements.end(); ++it){
//        l->addElement((*it)->eval(e));
//    }
//    return l;
    return this;
}

void List::print(){
    cout << "(";
    for (vector<Array*>::const_iterator it = elements.begin(); it != elements.end(); ++it){
        if (it != elements.begin()) { 
            cout << " ";
        }
        if ((*it)->isAtom()){
            ((DataType*) (*it))->print();
        }
    }
    cout << ")";
}

void List::addElement(Array *element) {
    elements.push_back(element);
}

string List::toString() {
    string result = "(";
    for (vector<Array*>::const_iterator it = elements.begin(); it != elements.end(); ++it){
        if (it != elements.begin()) { 
            result += " ";
        }
        result += (*it)->toString();
    }
    result += ")";
    return result;
}
