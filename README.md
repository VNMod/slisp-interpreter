# slisp_interpreter

### Date: April 2021

## Task:

To design and implement an interpreter for a simple programming language called *slisp*, and build a graphical interface for the same.

## Criteria:

* To create an expression-based language using prefix Lisp notation.
* To build thorough unit test cases for ensuring good modular functionality.
* To implement a Qt application using a variety of design techniques including dynamic polymorphism, composition, and event-driven programming.
* To practice good code quality and coverage as well as memory leak free programming.


## Important Aspects and Limitations:

### 

### 

### 

### Running it locally (Vagrant VM required):

- Add CMake to the path variable by running the following command in the Terminal:
  ```
  PATH="/Applications/CMake.app/Contents/bin":"$PATH
  ```
  
- Then, generate the build and configuration files (it uses the CMakeLists.txt file that enlists the source, targets and executables) with this command:

  ```
  cmake .
  ```
  
- This should create all the necessary configuration files and the executable. This project should have a **detect.cpp** file that detects the viruses and by running the   ```make``` command, the executable for this **detect.cpp** file is created.

- Then run the generated executable. You run the detect executable as follows:

  ```
  ./detect list binfile
  ```
 
  
  
