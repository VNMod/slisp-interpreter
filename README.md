# slisp_interpreter

### Date: April 2021, Virginia Tech ECE3574 Applied Software Design

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
- An Atom has a type and value. The type may be None, Boolean, Number, Symbol, Point, Line, Arc.
  1. None indicates that the expression has no value. 
  2. The possible values of a Boolean are True or False. 
  3. The possible values of Number are double floating point values. 
  4. The possible values of a Symbol is any string, not containing white-space, not possible to be parsed as a Number, not beginning with a numerical digit, and not a special form *define*, *begin*, or *if*.
  5. The possible values of a Point is a value of two coordinates of type Number.
  6. The possible values of a Line is a value of two Points.
  7. The possible values ofn Arc is a value of two Points and a Number. The first Point is the center of the arc, the second is the starting point of the arc, and the number is the spanning angle in radians.


- An expression is an Atom or a special form, followed by a possible list of Expressions surrounded by parenthesis and separated by spaces.
- The syntax for an expression is:
  1. &lt;atom&gt;
  2. (&lt;atom&gt;)
  3. (&lt;atom&gt; &lt;expression&gt; &lt;expression&gt; ...)
  
- The language has three special forms that makes use of four special-form expressions **define**, **begin**, **if** and **draw**:
  1. **(define &lt;symbol&gt; &lt;expression&gt;)** which adds a mapping from the symbol to the result of the expression into the environment. It is an error to redefine a symbol.
  2. **(begin &lt;expression&gt; &lt;expression&gt; ...)** which evaluates each expression in order, evaluating to the last.
  3. **(if &lt;expression1&gt; &lt;expression2&gt; &lt;expression3&gt;)** which evaluates to the result of &lt;expression2&gt; if &lt;expression1&gt; evalutes to True, else it evaluates to the result of &lt;expression3&gt;.
  4. **(draw &lt;graphical type expression1&gt; ... &lt;graphical type expression N&gt;)** where graphical type expressions are either a Point, Line or Arc.

- The language supports the following procedures: **not**, **and**, **or**, **<**, **>**, **<=**, *>=*, **=**, **+**, **-** for negative arguments and subtraction, ***, */*, *log10*, *pow*, **sin**, **cos**, **arctan**.


## Interfaces:

### Text-Based Interpreter Program Interface:

#### Short Programs in the Terminal:

- In order to execute short simple program, we pass a flag **-e** followed by a quoted string with the program. For example:

```./slisp -e "(+ 3 (- 2) 10)"```

- In case of error, the appropriate semantic or syntax error messages are displayed in the terminal.


#### External Scripts of a Program:

- We can execute programs stored in external files as follows:

```./slisp mycode.slp``` where mycode.slp is a .slp file that denotes that it contains slisp script code within.


#### Interactive REPL in the Terminal:

- This (Read-Evaluate-Print-Loop) option allows the user to interactively create programs in the slisp environment.
- In order to begin the REPL option, we must type in the generated executable's name:

```./slisp```

- This prints a **slisp>** prompt and waits for the user to type an expression onto standard input. The entered expression is then evaluated and its resultant expression is printed. 
- In case of a semantic error, the environment reverts to a state prior to the recent evaluation.
- After printing the result, the REPL prompts the user with **slisp>** again for another expression.
- To exit the REPL, the user must type in the EOF character.


### GUI Interface:

- The GUI interface has three important widgets: the Message Widget, Canvas Widget, REPLWidget.
- The bottom-most widget is the REPL Widget which is where users can enter any expressions.
- The top-most widget is the Message Widget which is a read-only message output window that allows users to see informational or error messages.
- The middle widget is the Canvas Widget which displays current drawings.


- This GUI interface is initiated with the following command in the terminal:
```./sldraw```

  
## Running it locally (Vagrant VM required)
 
 - The repository contains a Vagrantfile that sets up the virtual machine with minimal graphical interaction enabled.
 - Initialize the environment with ```vagrant up```.
 - Reboot the machine using ```vagrant halt```, followed by ```vagrant up``` (only required to be done once when the vagrant environment is being created for the first time).

- Use ```cd /vagrant``` to navigate to the right directory. Then ```cmake /vagrant``` and ```make``` to build the required configuration files.
- Then, run the appropriate interface using either ```./slisp``` or ```./sldraw``` as mentioned above.
  
  
