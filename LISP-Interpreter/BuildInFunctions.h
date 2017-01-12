#include "Function.h"
#include "Enviroment.h"
#include "Nil.h"
#include "Number.h"
#include "String.h"

#ifndef BUILDINFUNCTIONS_H
#define BUILDINFUNCTIONS_H

class BuildInPlus : public Function {
private:
    DataType* sumNubers(Enviroment *e);
    DataType* sumStrings(Enviroment *e);
public:
    BuildInPlus();
    virtual ~BuildInPlus();
    virtual DataType* eval(Enviroment *e);
};




#endif /* BUILDINFUNCTIONS_H */

