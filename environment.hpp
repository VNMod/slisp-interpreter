#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

// system includes
#include <map>

// module includes
#include "expression.hpp"

class Environment
{
private:
  // Environment is a mapping from symbols to expressions or procedures
  enum EnvResultType
  {
    ExpressionType,
    ProcedureType
  };
  struct EnvResult
  {
    EnvResultType type;
    Expression exp;
    Procedure proc;
  };

  std::map<Symbol, EnvResult> envmap;

public:
  // default constructor that initializes the default environment
  Environment();

  // inserting the mappings for keywords
  void keywords();

  // inserting the mappings for logical procedures
  void logicalprocedures();

  // inserting the mappings for comparison procedures
  void comparisonprocedures();

  // inserting the mappings for basic arithmetic procedures
  void basicarithmeticprocedures();

  // inserting the mappings for logarithmic and power procedures
  void lognpowprocedures();

  // inserting the mappings for graphic procedures
  void graphicprocedures();

  // inserting the mappinds for trigonometric procedures
  void trigonometricprocedures();

  // inserting the mappings for special expressions like PI
  void specialexpressions();

  // returns the procedure (of an EnvResult object in the existing environment) for a given Symbol
  Procedure searchProc(Symbol x);

  // returns the equivalent expression value (as stored in the default environment) for a given symbol such as "pi"
  Expression searchExp(Symbol pi);

  // inserts a mapping into the environment for a given symbol and expression
  void insertexp(Symbol x, Expression y);

  // inserts a mapping into the environment for a given symbol and procedure
  void insertproc(Symbol x, Procedure y);

  // checks if there is an existing mapping within the environment for a given symbol
  bool check(Symbol x)
  {
    std::map<Symbol, EnvResult>::iterator it;

    bool flag = false;

    it = envmap.find(x);
    if (it != envmap.end()) //if found, map is returned
    {
      flag = true;
    }

    return flag;
  }

  // returns the environment mapping for a given symbol
  std::map<Symbol, EnvResult> search(Symbol x)
  {
    std::map<Symbol, EnvResult>::iterator it;

    it = envmap.find(x);
    if (it != envmap.end()) //if found, map is returned
    {
      return envmap;
    }
  }

  // returns the EnvResult (value) from an existing mapping in the environment for a given symbol (key)
  EnvResult &operator[](const Symbol &x)
  {
    std::map<Symbol, EnvResult>::iterator it;

    it = envmap.find(x);

    return it->second;
  }

  // clears the 'envmap' Environment variable
  void clearmap()
  {
    envmap.clear();
  }
};

// List of functions that find the procedure to be performed on a given vector of Atom type arguments
// and returns the resultant expression on performing this procedure.

Expression not_proc(const std::vector<Atom> &args);
Expression and_proc(const std::vector<Atom> &args);
Expression or_proc(const std::vector<Atom> &args);
Expression lessthan_proc(const std::vector<Atom> &args);
Expression lessthaneq_proc(const std::vector<Atom> &args);
Expression greaterthan_proc(const std::vector<Atom> &args);
Expression greaterthaneq_proc(const std::vector<Atom> &args);
Expression equal_proc(const std::vector<Atom> &args);
Expression add_proc(const std::vector<Atom> &args);
Expression sub_proc(const std::vector<Atom> &args);
Expression mul_proc(const std::vector<Atom> &args);
Expression div_proc(const std::vector<Atom> &args);
Expression Log10_proc(const std::vector<Atom> &args);
Expression pow_proc(const std::vector<Atom> &args);
Expression point_proc(const std::vector<Atom> &args);
Expression line_proc(const std::vector<Atom> &args);
Expression arc_proc(const std::vector<Atom> &args);
Expression sin_proc(const std::vector<Atom> &args);
Expression cos_proc(const std::vector<Atom> &args);
Expression arctan_proc(const std::vector<Atom> &args);

#endif
