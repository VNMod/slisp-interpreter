#include "interpreter.hpp"

// system includes
#include <stack>
#include <stdexcept>
#include <iostream>

// module includes
#include "tokenize.hpp"
#include "expression.hpp"
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"

Interpreter::Interpreter(){};

bool Interpreter::parse(std::istream &expression) noexcept
{
  // Parse and Tokenize the passed expression
  TokenSequenceType listOfTokens = tokenize(expression);

  try
  {
    // Build the AST
    ast = read_from_tokens(listOfTokens);

    if (!listOfTokens.empty()) //throw an error in case of extra input tokens
    {
      throw std::invalid_argument("Error. The expression has excess tokens!");
    }
  }
  catch (const std::invalid_argument &e)
  {
    return false;
  }

  return true;
};

Expression Interpreter::read_from_tokens(TokenSequenceType &listOfTokens)
{
  if (listOfTokens.empty()) // throw an error if the list of tokens are empty
  {
    throw std::invalid_argument("Error. The expression has no valid tokens. Invalid statement error!");
  }

  if (listOfTokens.size() == 1 && listOfTokens[0] != ")") // throw an error if there's no matching parenthesis at the end
  {
    throw std::invalid_argument("Error. No matching parenthesis at the end.");
  }

  Atom atom;
  std::string token = listOfTokens[0];

  listOfTokens.pop_front();

  if (token == "(")
  {
    Expression exp;
    Atom head;

    // The first token encountered, after the '(' token is popped, is now the head of this new expression
    token_to_atom(listOfTokens[0], exp.head);

    bool emptyexp = true; // flag that ensures empty expressions such as () are not valid

    while (listOfTokens[0] != ")")
    {
      emptyexp = false;
      Expression x;
      x = read_from_tokens(listOfTokens);

      exp.tail.push_back(x);
    }

    if (emptyexp) // required for examples such as: "()"
    {
      throw std::invalid_argument("Error due to empty expression.");
    }

    if (!listOfTokens.empty())
    {
      listOfTokens.pop_front(); // pop the ) token as it has been encountered
    }
    return exp;
  }
  if (token == ")")
  {
    throw std::invalid_argument("Error. A closing paren has been encountered. Invalid statement error!");
  }

  Expression e;
  if (token_to_atom(token, e.head))
  {
    return e;
  }

  throw std::invalid_argument("Error. Invalid Case");
}

Expression Interpreter::eval()
{
  // TODO: implement this function

  Environment *envp = &env;
  Expression evaluated_exp;

  evaluated_exp = evaluate(ast, envp); // finds out the evaluation of the formed AST

  return evaluated_exp;
}

Expression Interpreter::evaluate(Expression ast, Environment *environ)
{

  Expression exp = evaluateothertypes(ast, environ);

  Expression nullexp;

  if (exp != nullexp)
  {
    return exp;
  }

  exp = evaluatespecialforms(ast, environ);

  nullexp.head.type = NullType;

  if (exp.head.type != nullexp.head.type)
  {
    return exp;
  }

  // Special symbols cannot be evaluated as they don't have any definitive procedure/expression mapping in the environment
  if (ast.head.value.sym_value == "@" || ast.head.value.sym_value == "%" || ast.head.value.sym_value == "^" || ast.head.value.sym_value == "$" || ast.head.value.sym_value == "#" || ast.head.value.sym_value == "!" || ast.head.value.sym_value == "&")
  {
    throw InterpreterSemanticError("Error (semantic). Special symbols such as @, %, ^, $ or #, !, & cannot be evaluated in an expression");
  }

  if (!ast.tail.empty())
  {
    evaluate(ast.tail[0], environ); //recursive call to reach the leftmost leaf nodes
  }

  // Evaluating a tail of expressions:

  std::vector<Atom> args;

  // args is a vector of arguments that stores the result of
  // evaluating all the tail members of an expression within the AST.

  for (int i = 0; i < ast.tail.size(); i++)
  {
    args.push_back(evaluate(ast.tail[i], environ).head);
  }

  // Note that the first argument will always be a symbol with a Procedure mapping in the default environment.
  // So, we now perform the procedure that the symbol maps to on the rest of the arguments (based on the operation).

  if (!args.empty())
  {
    return environ->searchProc(args[0].value.sym_value)(args);
  }

  return ast;
}

void Interpreter::resetenv()
{
  env.clearmap(); //cleared the map

  Environment default_env;

  // env = default_env;
  // could have also done this ^^^, but I just re-inserted the mappings for the default environment once again.

  // Special Expressions:

  env.insertexp("define", default_env.operator[]("define").exp);
  env.insertexp("begin", default_env.operator[]("begin").exp);
  env.insertexp("if", default_env.operator[]("if").exp);
  env.insertexp("draw", default_env.operator[]("draw").exp);

  // All the Procedures:

  env.insertproc("not", default_env.operator[]("not").proc);
  env.insertproc("and", default_env.operator[]("and").proc);
  env.insertproc("or", default_env.operator[]("or").proc);
  env.insertproc("<", default_env.operator[]("<").proc);
  env.insertproc("<=", default_env.operator[]("<=").proc);
  env.insertproc(">", default_env.operator[](">").proc);
  env.insertproc(">=", default_env.operator[](">=").proc);
  env.insertproc("=", default_env.operator[]("=").proc);
  env.insertproc("+", default_env.operator[]("+").proc);
  env.insertproc("-", default_env.operator[]("-").proc);
  env.insertproc("*", default_env.operator[]("*").proc);
  env.insertproc("/", default_env.operator[]("/").proc);
  env.insertproc("log10", default_env.operator[]("log10").proc);
  env.insertproc("pow", default_env.operator[]("pow").proc);
  env.insertproc("point", default_env.operator[]("point").proc);
  env.insertproc("line", default_env.operator[]("line").proc);
  env.insertproc("arc", default_env.operator[]("arc").proc);
  env.insertproc("sin", default_env.operator[]("sin").proc);
  env.insertproc("cos", default_env.operator[]("cos").proc);
  env.insertproc("arctan", default_env.operator[]("arctan").proc);

  // PI:

  env.insertexp("pi", default_env.operator[]("pi").exp);
}

Expression Interpreter::evaluateothertypes(Expression ast, Environment *environ)
{
  if (ast.head.type == SymbolType)
  {
    if (env.check(ast.head.value.sym_value)) // if the environment symbol exists, find the mapping
    {
      return environ->searchExp(ast.head.value.sym_value);
    }
  }
  if (ast.head.type == NumberType)
  {
    return ast;
  }
  if (ast.head.type == BooleanType)
  {
    return ast;
  }
  if (ast.head.type == LineType)
  {
    return ast;
  }
  if (ast.head.type == ArcType)
  {
    return ast;
  }
  if (ast.head.type == PointType)
  {
    return ast;
  }

  Expression exp;
  return exp;
}

Expression Interpreter::evaluatebegin(Expression ast, Environment *environ)
{
  // All expressions but the last one must be evaluated first.
  for (int i = 1; i < ast.tail.size() - 1; i++)
  {
    evaluate(ast.tail[i], environ);
  }

  // Then, the result of evaluating the last expression must be returned back as the final result.
  return evaluate(ast.tail[ast.tail.size() - 1], environ);
}

Expression Interpreter::evaluatedefine(Expression ast, Environment *environ)
{
  if (ast.tail.size() != 3)
  {
    throw InterpreterSemanticError("Error (semantic). 'if' is ternary. Only 3 arguments are required");
  }

  if (ast.tail[1].head.type != SymbolType)
  {
    throw InterpreterSemanticError("Error (semantic). the expression <1> must be of Symbol Type where the format is 'define <1><2>'");
  }

  if (environ->check(ast.tail[1].head.value.sym_value))
  {
    std::string error = "Error (semantic). Expression <1> which is symbol (" + ast.tail[1].head.value.sym_value + ") already exists";
    throw InterpreterSemanticError(error);
  }

  // For "define <1> <2>"" where <1> is a symbol expression (or expression with a head of Symbol type)
  // And, <2> is the expression to be evaluated.
  // The environment needs to be updated once expression <2> is evaluated for a given symbol expression <1>

  Expression result = evaluate(ast.tail[2], environ); //the result of evaluating expression <2>

  //adding a mapping for a symbol type key (i.e. the symbol value of expression <1>) and a value of the result of expression <2>
  environ->insertexp(ast.tail[1].head.value.sym_value, result);

  return result;
}

Expression Interpreter::evaluateif(Expression ast, Environment *environ)
{
  if (ast.tail.size() != 4)
  {
    throw InterpreterSemanticError("Error (semantic). if is quad-ary. Only 4 arguments are required");
  }

  // Evaluate expression 1:
  Expression e = evaluate(ast.tail[1], environ);

  if (e.head.type == BooleanType)
  {
    // if the result of <expression 1> is true, <expression 2> is evaluated
    // and the result of that expression is returned as the final result.
    if (e.head.value.bool_value)
    {
      return evaluate(ast.tail[2], environ);
    }
    // else if the result of <expression 1> is false, <expression 3> is evaluated
    // and the result of that expression is returned as the final result.
    if (!e.head.value.bool_value)
    {
      return evaluate(ast.tail[3], environ);
    }
  }

  throw InterpreterSemanticError("Error (semantic). Expression 1 must be a Boolean type");
}

Expression Interpreter::evaluatedraw(Expression ast, Environment *environ)
{

  // must be an m-ary expression
  if (ast.tail.size() < 2)
  {
    throw InterpreterSemanticError("Error (semantic). draw is m-ary. 0 arguments are not allowed.");
  }

  // evaluate all the following tailed expressions
  for (int i = 1; i < ast.tail.size(); i++)
  {
    graphics.push_back(evaluate(ast.tail[i], environ).head);
  }

  Expression noneexp;
  noneexp.head.type = NoneType;

  return noneexp;
}

Expression Interpreter::evaluatespecialforms(Expression ast, Environment *environ)
{
  if (ast.head.value.sym_value == "begin") //Syntax: (begin <expression> <expression> ...)
  {
    return evaluatebegin(ast, environ);
  }
  if (ast.head.value.sym_value == "define") // Syntax: (define <symbol> <expression>)
  {
    return evaluatedefine(ast, environ);
  }
  if (ast.head.value.sym_value == "if") // Syntax: (if <expression1> <expression2> <expressions3>)
  {
    return evaluateif(ast, environ);
  }
  if (ast.head.value.sym_value == "draw")
  {
    return evaluatedraw(ast, environ);
  }

  Expression noneexp;
  noneexp.head.type = NullType;
  return noneexp; // return a Nonetype expression
}