/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LispStack.h
 * Author: jakub
 *
 * Created on Štvrtok, 2017, januára 12, 17:43
 */

#ifndef LISPSTACK_H
#define LISPSTACK_H

class LispStack {
    public:
        static LispStack& getInstance()
        {
            static LispStack instance;
            return instance;
        }
    private:
        S() {}
        S(LispStack const&);              
        void operator=(LispStack const&); 
};


#endif /* LISPSTACK_H */

