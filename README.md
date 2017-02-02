# RUN-LISP
Toto je semestrálna práca predmetu MI-RUN. Autori: Jakub Chlup, Filip Sakala. 
Implementovaný je interpret pre vlastnú podmnožinu jazyka LISP. Implementovali sme v C++.

# Spustenie
Ako netbeans projekt -> Run (alebo použiť netbeans makefile/skompilovať klasicky s g++).
- testy sú písané ako CppUnit testy:
http://cppunit.sourceforge.net/doc/cvs/cppunit_cookbook.html

# Naša podmnožina jazyka LISP podporuje:
- Základné typy: Celé číslo (Number), String, Symbol, True, False, Nil
- Built-in funkcie: + - * == defconst, defvar, <, >, ==, undef
- Definícia premennej: (defvar x 5)
- Definícia konštanty: (defconst x 5)
- Definícia funkcie: (def f (x y z) (+ x y z) (- x y))
- Vymazanie premennej/funkcie: (undef x)
- Podmienky: (if (== 1 1) true false)
- Logické spojky: (== 1 1), (&& true false), (|| true false)
- For cyklus: (for i from 1 to 10 do (+ i 5))
- vstup a výstup do konzoly
- REPL (Read-Eval-Print-Loop)
- dynamickú alokáciu pamäti (Mark&Sweep garbage collector)

# Príklady použitia aj s výstupmi
```sh
Welcome to LISP interpreter
1. > 1
1 (number)
2. > "hello"
"hello" (string)
3. > x
Symbol x not found in environment. (error)
4. > true
true (true)
5. > nil
nil (nil)
6. > (defvar x 0)  
0 (parameter)
7. > x
0 (parameter)
8. > (def inc (x) (+ x 1))
inc (symbol)
9. > (inc x)
1 (number)
10. > (inc (inc (inc (inc (inc (inc (inc x)))))))
7 (number)
11. > (if true true false)
true (true)
12. > (if (== 0 0) (+ 0 1) (- 0 1))
1 (number)
13. > (for i from 0 to 10 do (defvar x (+ x 1)))
10 (parameter)
14. > x
10 (parameter)
15. > (if (== x 10) "correct" "error")
"correct" (string)
16. > (defconst c 5)
5 (parameter)
17. > (defconst c 6)
Can't change value of constant (error)
18. > (undef x)
true (true)
19. > x
Symbol x not found in environment. (error)
20. > (undef +)
true (true)
21. > (+ 1 2)
Call to undefined function +
```

# Zložitejšie príklady
## Fibonacci
```sh
(def fib (n) 
(defvar p1 1) 
(defvar p2 1) 
(for i from 1 to (- n 1) do 
(defvar p3 (+ p1 p2)) 
(defvar p1 p2) 
(defvar p2 p3)
)
(return p2)
)
```
### Použitie

```sh
Welcome to LISP interpreter
1. > (def fib (n) 
(defvar p1 1) 
(defvar p2 1) 
(for i from 1 to (- n 1) do 
(defvar p3 (+ p1 p2)) 
(defvar p1 p2) 
(defvar p2 p3)
)
(return p2)
)
fib (symbol)
2. > (fib 1)
1 (number)
3. > (fib 2)
1 (number)
4. > (fib 3)
2 (number)
5. > (fib 4)
3 (number)
6. > (fib 5)
5 (number)
7. > (fib 6)
8 (number)
```

## Sort
```sh
(def bubblesort (x) 
(for i from 0 to (length x) do 
(for j from 0 to (length x) do 
(if (> (at x j) (at x (+ j 1))) 
(
(defvar pom (at x j)) 
(set x j (at x (+ j 1))) 
(set x (+ j 1) pom)) x)
)))
```
### Použitie

```sh
Welcome to LISP interpreter
1. > (def bubblesort (x) 
(for i from 0 to (length x) do 
(for j from 0 to (length x) do 
(if (> (at x j) (at x (+ j 1))) 
(
(defvar pom (at x j)) 
(set x j (at x (+ j 1))) 
(set x (+ j 1) pom)) x)
)))
bubblesort (symbol)
2. > (bubblesort (list 21 5 85 21 5632 5 22 1 11 1))
(1 1 5 5 11 21 21 22 85 5632) (list)
```
