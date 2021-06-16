#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

// system includes
#include <string>
#include <istream>
#include <vector>

// module includes
#include "expression.hpp"
#include "environment.hpp"
#include "tokenize.hpp"

// Interpreter has
// Environment, which starts at a default
// parse method, builds an internal AST
// eval method, updates Environment, returns last result
class Interpreter
{
public:
  // Default constructor for the interpreter
  Interpreter();

  // Parses the list of tokens and creates an internal AST (Abstract Syntax Tree)
  bool parse(std::istream &expression) noexcept;

  // Evaluates the created AST, and returns a resultant expression
  Expression eval();

  // Recursive helper function that creates the AST from the provided list of valid tokens
  Expression read_from_tokens(TokenSequenceType &listOfTokens);

  // Resets the environment variable (env) -- clears, and inserts a default configuration
  void resetenv();

  Environment returnenv()
  {
    return env;
  }

  std::vector<Atom> getGraphicsatoms()
  {
    return graphics;
  }

  void clearGraphics()
  {
    graphics.clear();
  }

  void clearAST()
  {
    ast.head.type = NoneType;
    ast.tail.clear();
  }

protected:
  // Environment configuration for the interpreter
  Environment env;
  // Abstract Syntax Tree Expression
  Expression ast;

  // Recursive helper function that evaluates the built AST
  // Note: the environment is updated with any define statements within the eval
  Expression evaluate(Expression ast, Environment *environ);

  Expression evaluateothertypes(Expression ast, Environment *environ);
  Expression evaluatespecialforms(Expression ast, Environment *environ);
  Expression evaluatebegin(Expression ast, Environment *environ);
  Expression evaluatedefine(Expression ast, Environment *environ);
  Expression evaluateif(Expression ast, Environment *environ);
  Expression evaluatedraw(Expression ast, Environment *environ);

  std::vector<Atom> graphics;
};

#endif
