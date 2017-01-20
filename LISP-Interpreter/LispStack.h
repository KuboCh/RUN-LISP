#include <stack>

#include "Function.h"

#ifndef LISPSTACK_H
#define LISPSTACK_H

using namespace std;

class LispStack {
    private:
        stack<Function*> stackOfFunctions;
        LispStack() {}
        LispStack(LispStack const&);              
        void operator=(LispStack const&);
    public:
        static LispStack& getInstance()
        {
            static LispStack instance;
            return instance;
        }
        Function* pop() {
            if (stackOfFunctions.empty()){
                return NULL;
            }
            Function *f = stackOfFunctions.top();
            stackOfFunctions.pop();
            return f;        
        }
        void push(Function *function){
            stackOfFunctions.push(function);
        }
        
};


#endif /* LISPSTACK_H */

