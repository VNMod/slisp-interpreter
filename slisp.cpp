#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "interpreter.hpp"
#include "interpreter_semantic_error.hpp"

int shortPrograms(int argc, char **argv, Interpreter slinterp);
int filePrograms(int argc, char **argv, Interpreter slinterp);
int REPL(int argc, char **argv, Interpreter slinterp);

void printresults(Expression result);

int main(int argc, char **argv)
{

  Interpreter slinterp; // slisp interpreter

  // MODE 1: SHORT PROGRAMS:

  if (argc > 2)
  {
    return shortPrograms(argc, argv, slinterp);
  }

  // MODE 2: Executing programs stored in external files:

  if (argc == 2)
  {
    return filePrograms(argc, argv, slinterp);
  }

  // MODE 3: interactive execution using a REPL

  if (argc == 1)
  {
    return REPL(argc, argv, slinterp);
  }

  return EXIT_SUCCESS;
}

int shortPrograms(int argc, char **argv, Interpreter slinterp)
{
  std::string arg1 = argv[1];

  if (arg1 == "-e") //if the passed flag is e (which indicates a short simple program)
  {
    std::string shortprogram = argv[2];

    std::istringstream sprog(shortprogram);

    Expression result;
    bool ok = slinterp.parse(sprog);

    if (!ok) // error due to incorrect parse
    {
      std::cout << "Error" << std::endl;
      return EXIT_FAILURE;
    }

    try
    {
      result = slinterp.eval();
    }
    catch (InterpreterSemanticError &e) // error caused by incorrect evaluation
    {
      std::cout << "Error" << std::endl;
      return EXIT_FAILURE;
    }

    printresults(result);

    return EXIT_SUCCESS;
  }
}

int filePrograms(int argc, char **argv, Interpreter slinterp)
{
  std::string arg1 = argv[1];

  if (arg1.find(".slp") != std::string::npos)
  {
    std::string fname = arg1;

    std::ifstream ifs(fname);

    if (!ifs) // if file does not exist
    {
      std::cout << "Error" << std::endl;
      return EXIT_FAILURE;
    }

    Expression result;
    bool ok = slinterp.parse(ifs);

    if (!ok) // error due to incorrect parse
    {
      std::cout << "Error" << std::endl;
      return EXIT_FAILURE;
    }

    try
    {
      result = slinterp.eval();
    }
    catch (InterpreterSemanticError &e) // error caused by incorrect evaluation
    {
      std::cout << "Error" << std::endl;
      return EXIT_FAILURE;
    }

    printresults(result);

    return EXIT_SUCCESS;
  }
  std::cout << "Error" << std::endl;
  return EXIT_FAILURE;
}

int REPL(int argc, char **argv, Interpreter slinterp)
{
  std::string exp;

  // runs the REPL until EOF is encountered
  // which is triggered by control D or control K (depending on OS)

  std::cout << "slisp> ";

  while (std::getline(std::cin, exp))
  {
    bool error = false;
    while (exp.empty() || exp == "\n")
    {
      std::cout << "slisp> ";
      std::cin >> exp;
    }

    Expression result;
    std::istringstream replprog(exp);

    bool ok = slinterp.parse(replprog);

    if (!ok) // error due to incorrect parse
    {
      std::cout << "Error" << std::endl;
    }
    else
    {
      try
      {
        result = slinterp.eval();
      }
      catch (InterpreterSemanticError &e) // error caused by incorrect evaluation
      {
        std::cout << "Error" << std::endl;

        // reset to default state:
        slinterp.resetenv();

        error = true;
      }

      if (!error)
      {
        printresults(result);
      }
    }

    std::cout << "slisp> ";
  }

  return EXIT_SUCCESS;
}

void printresults(Expression result)
{
  if (result.head.type == NumberType)
  {
    std::cout << "(" << result.head.value.num_value << ")" << std::endl;
  }
  else if (result.head.type == BooleanType)
  {
    if (result.head.value.bool_value)
    {
      std::cout << "("
                << "True"
                << ")" << std::endl;
    }
    else if (!result.head.value.bool_value)
    {
      std::cout << "("
                << "False"
                << ")" << std::endl;
    }
  }
  else if (result.head.type == PointType)
  {
    std::cout << "(" << result.head.value.point_value.x << "," << result.head.value.point_value.y << ")" << std::endl;
  }
  else if (result.head.type == LineType)
  {
    std::cout << "((" << result.head.value.line_value.first.x << "," << result.head.value.line_value.first.y << ")(" << result.head.value.line_value.second.x << "," << result.head.value.line_value.second.y << "))" << std::endl;
  }
  else if (result.head.type == ArcType)
  {
    std::cout << "((" << result.head.value.arc_value.center.x << "," << result.head.value.arc_value.center.y << ")(" << result.head.value.arc_value.start.x << "," << result.head.value.arc_value.start.y << ")(" << result.head.value.arc_value.span << "))" << std::endl;
  }
}