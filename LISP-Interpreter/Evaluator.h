#include "DataType.h"
#include "Array.h"
#include "Enviroment.h"
#include <string>
#include <vector>

#ifndef EVALUATOR_H
#define EVALUATOR_H

class Evaluator {
public:
    Evaluator();
    Evaluator(const Evaluator& orig);
    virtual ~Evaluator();
    DataType* eval(Array* tokens, Enviroment& e);
private:

};

#endif /* EVALUATOR_H */

