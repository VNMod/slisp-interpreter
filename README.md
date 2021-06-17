# slisp_interpreter

### Date: April 2021

## Description:

An application for a simple expression-based programming language called slisp based on prefix Lisp notation.

## Criteria:

* To design and implement an interpreter for a simple expression-based programming language called *slisp* using prefix Lisp notation.
* To build thorough unit test cases for ensuring good modular functionality.
* To implement a Qt application using a variety of design techniques including dynamic polymorphism, composition, and event-driven programming.
* To practice good code quality and coverage as well as memory leak free programming.

## Concepts Covered:


## Overview:

### RULES:

- As slisp uses prefix notation it places an operator first like this expression: 
  (/ (* (- 3 2) 4) 2) is the same as (((3 - 2) * 4)/2)
  
- The *syntax* for an expression is (PROC ARG1 ... ARGN), where PROC is a procedure and ARG1 ... ARGN are arguments that can also be expressions.
  
- Let's take this expression for example ```(define x (/ (* (- 3 2) 4) 2))```
  1. define here is a procedure
  2. x is a symbol whose value is computed to be the result of the numerical expression (/ (* (- 3 2) 4) 2))
  3. Now, x has a defined mapping in the existing programming environment, so every use of it in an arithmetic expression would be replaced by the resultant value 2.

### SYNTAX:

- The structure of the language is made up of either an *Atom* or *Expression*.
- An Atom has a type and value. The type may be None, Boolean, Number, or Symbol. 
  1. None indicates that the expression has no value. 
  2. The possible values of a Boolean are True or False. 
  3. The possible values of Number are double floating point values. 
  4. The possible values of a Symbol is any string, not containing white-space, not possible to be parsed as a Number, not beginning with a numerical digit, and not a special form *define*, *begin*, or *if*.
- An expression is an Atom or a special form, followed by a possible list of Expressions surrounded by parenthesis and separated by spaces.
- The syntax for an expression is:
  1. <atom>
  2. (<atom>)
  3. (<atom> <expression> <expression> ...)
  
- The language has three special forms that makes use of three special-form expressions *define*, *begin*, and *if*:
  1. (define <symbol> <expression>) which adds a mapping from the symbol to the result of the expression into the environment. It is an error to redefine a symbol.
  2. (begin <expression> <expression> ...) which evaluates each expression in order, evaluating to the last.
  3. (if <expression1> <expression2> <expression3>) which evaluates to the result of <expression2> if <expression1> evalutes to True, else it evaluates to the result of <expression3>.



## Running it locally (Vagrant VM required)
 
  
  
