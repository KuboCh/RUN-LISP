#include <string>
#include <vector>

#ifndef EVALUATOR_H
#define EVALUATOR_H
class DataType;
class Array;
class Enviroment;

class Evaluator {
public:
    Evaluator();
    Evaluator(const Evaluator& orig);
    virtual ~Evaluator();
    DataType* eval(Array* tokens, Enviroment& e);
private:

};

#endif /* EVALUATOR_H */

