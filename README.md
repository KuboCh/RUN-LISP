# RUN-LISP
Toto je semestrálna práca predmetu MI-RUN. Autori: Jakub Chlup, Filip Sakala. 
Implementovaný je interpret pre vlastnú podmnožinu jazyka LISP. Implementovali sme v C++.

# Spustenie
Ako netbeans projekt -> Run (alebo použiť netbeans makefile/skompilovať klasicky s g++).
- testy sú písané ako CppUnit testy:
http://cppunit.sourceforge.net/doc/cvs/cppunit_cookbook.html

# Naša podmnožina jazyka LISP podporuje:
- Základné typy: Celé číslo (Number), String, Symbol, True, False, Nil
- Built-in funkcie: + - * == defconst, defvar list
- Definícia premennej: (defvar x 5)
- Definícia konštanty: (defconst x 5)
- Definícia funkcie: (def f (x y z) (+ x y z) (- x y))
- Podmienky: (if (== 1 1) true false)
- For cyklus: (for i from 1 to 10 do (+ i 5))
- vstup a výstup do konzoly
- REPL (Read-Eval-Print-Loop)
- dynamickú alokáciu pamäti (Mark&Sweep garbage collector)
