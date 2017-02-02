#include <list>
#include <stack>

#include "Environment.h"
#include "Variable.h"
#include "LispStack.h"
#include "Function.h"
#include "Parser.h"

using namespace std;

#ifndef MEMORY_H
#define MEMORY_H

class Memory {
private:
    list<Environment*> free;
    list<Environment*> allocated;
    int memsize; // maxsize of acutal free memory

    Memory() {
        memsize = 1;
        // push init memory here
        for (int i = 0; i < memsize; i++) {
            free.push_back(new Environment());
        }
    }
    Memory(Memory const&);
    void operator=(Memory const&);

    Environment* pop() {
        if (free.empty()) {
            return NULL;
        }
        Environment* d = (*free.begin());
        free.pop_front();
        allocated.push_back(d);
        return d;
    }

public:

    static Memory& getInstance() {
        static Memory instance;
        return instance;
    }

    /*
     * Get one piece of memory (DataType). If there's not enough memory, use 
     * mark&sweep, then realloc if needed.
     */
    Environment* get() {
        if (free.size() == 0) {
            if (Parser::PRINT)
                cout << "Memory needs more space. Memsize = " << memsize << endl;
            mark();
            sweep();
            if (free.size() == 0)
                realloc();
        }
        return pop();
    }

    void mark() {
        // init mark
        for (list<Environment*>::iterator it = allocated.begin(); it != allocated.end(); ++it) {
            (*it)->mark = false;
        }
        // mark all stacked (=used) environments
        stack<Function*> stackOfFunctions;
        while (!LispStack::getInstance().isEmpty()) { // go through stack
            Function* f = LispStack::getInstance().pop();
            if (f->functionEnvironment)
                f->functionEnvironment->mark = true;
            stackOfFunctions.push(f);
        }
        while (!stackOfFunctions.empty()) { // push it back
            Function* f = stackOfFunctions.top();
            stackOfFunctions.pop();
            LispStack::getInstance().push(f);
        }
    }

    void sweep() {
        // check unmarked & sweep
        for (list<Environment*>::iterator it = allocated.begin(); it != allocated.end(); ) {
            if (!(*it)->mark) {
                if (Parser::PRINT)
                    cout << "sweep!" << endl;
                (*it)->empty(); // remove variables and functions inside
                free.push_back(*it);
                it = allocated.erase(it); // delete and return next
            } else {
                ++it;
            }
        }
    }

    void realloc() {
        if (Parser::PRINT)
            cout << "Realloc" << endl;
        int oldMemsize = memsize;
        memsize *= 2;
        for (int i = oldMemsize; i < memsize; i++)
            free.push_back(new Environment());
    }
};

#endif /* MEMORY_H */

