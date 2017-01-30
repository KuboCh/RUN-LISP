#include "DataType.h"

DataType::DataType() {
}

DataType::DataType(const DataType& orig) {
}

DataType::~DataType() {
}

DataType* DataType::eval(Environment& e) {
    cout << "Abstract DataType eval() should be overriden." << endl;
    return NULL;
}

void DataType::print() {
    cout << "Abstract DataType print should be overriden." << endl;
}

int DataType::dataType() {
    cout << "Abstract DataType type() should be overriden." << endl;
    return TYPE_ERROR;
}

string DataType::toString() {
    cout << "Abstract DataType type() should be overriden." << endl;
    return "";
}

/*
 * Translates data type to human-readable format (for printing to output).
 */
string DataType::typeToString() {
        string result = "unknown";
        switch (dataType()) {
            case 0: result = "number";
                break;
            case 1: result = "string";
                break;
            case 2: result = "list";
                break;
            case 3: result = "false";
                break;
            case 4: result = "true";
                break;
            case 5: result = "nil";
                break;
            case 6: result = "error";
                break;
            case 7: result = "parameter";
                break;
            case 8: result = "void";
                break;
            case 9: result = "symbol";
                break;
            case 10: result = "function";
                break;
        }
        return result;
    }