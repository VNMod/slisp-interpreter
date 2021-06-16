#include "environment.hpp"

#include <cassert>
#include <cmath>
#include <math.h>
#include <iostream>

#include "interpreter_semantic_error.hpp"

Environment::Environment()
{
  // Implementing environment conditions for three special-form
  // expression types:
  // 1. define 2. begin and 3. if
  // They are of the form:
  // (define <symbol> <expression>)
  // (begin <expression> <expression> ...)
  // (if <expression1> <expression2> <expressions3>)

  keywords();

  // Implementing environment conditions for the rest of the
  // expression forms called: procedures.
  // Common syntax is: (<symbol> <expression> <expression> ...)
  // They take one or more arguments and return an expression
  // according to their name.
  // These are m-ary based on the number of arguments and thus have
  // an arity of 1, 2,...m

  logicalprocedures();
  comparisonprocedures();
  basicarithmeticprocedures();
  lognpowprocedures();
  graphicprocedures();
  trigonometricprocedures();

  // Special Symbol - Pi which evaluates to atan2(0, -1)

  specialexpressions();
}

void Environment::keywords()
{
  EnvResult Define, Begin, If, Draw;

  Define.type = ExpressionType;
  Begin.type = ExpressionType;
  If.type = ExpressionType;
  Draw.type = ExpressionType;

  std::pair<Symbol, EnvResult> define_spform("define", Define);
  std::pair<Symbol, EnvResult> begin_spform("begin", Begin);
  std::pair<Symbol, EnvResult> if_spform("if", If);
  std::pair<Symbol, EnvResult> draw_spform("draw", Draw);

  Define.exp.head.type = SymbolType;
  Begin.exp.head.type = SymbolType;
  If.exp.head.type = SymbolType;
  Draw.exp.head.type = SymbolType;

  envmap.insert(define_spform);
  envmap.insert(begin_spform);
  envmap.insert(if_spform);
  envmap.insert(draw_spform);
}

void Environment::logicalprocedures()
{
  EnvResult Not, And, Or; //logical procedures

  // note: since a vector of atoms is a Procedure which is a function pointer
  // we reference the address using & (ampersand)
  Not.type = ProcedureType;
  Not.proc = (&not_proc); // Here, for example the procedure is layout for a logical not operation
  And.type = ProcedureType;
  And.proc = (&and_proc);
  Or.type = ProcedureType;
  Or.proc = (&or_proc);

  std::pair<Symbol, EnvResult> not_proce("not", Not);
  std::pair<Symbol, EnvResult> and_proce("and", And);
  std::pair<Symbol, EnvResult> or_proce("or", Or);

  // inserting the mappings for these procedures into the map for the environment variable:

  envmap.insert(not_proce);
  envmap.insert(and_proce);
  envmap.insert(or_proce);
}

void Environment::comparisonprocedures()
{
  EnvResult lessthan, lessthaneq, greaterthan, greaterthaneq, equal; //comparison procedures

  lessthan.type = ProcedureType;
  lessthan.proc = (&lessthan_proc);
  lessthaneq.type = ProcedureType;
  lessthaneq.proc = (&lessthaneq_proc);
  greaterthan.type = ProcedureType;
  greaterthan.proc = (&greaterthan_proc);
  greaterthaneq.type = ProcedureType;
  greaterthaneq.proc = (&greaterthaneq_proc);
  equal.type = ProcedureType;
  equal.proc = (&equal_proc);

  std::pair<Symbol, EnvResult> lessthan_proce("<", lessthan);
  std::pair<Symbol, EnvResult> lessthanequal_proce("<=", lessthaneq);
  std::pair<Symbol, EnvResult> greaterthan_proce(">", greaterthan);
  std::pair<Symbol, EnvResult> greaterthaneq_proce(">=", greaterthaneq);
  std::pair<Symbol, EnvResult> equal_proce("=", equal);

  envmap.insert(lessthan_proce);
  envmap.insert(lessthanequal_proce);
  envmap.insert(greaterthan_proce);
  envmap.insert(greaterthaneq_proce);
  envmap.insert(equal_proce);
}

void Environment::basicarithmeticprocedures()
{
  EnvResult add, sub, mul, div; //basic arithmetic operational procedures

  add.type = ProcedureType;
  add.proc = (&add_proc);
  sub.type = ProcedureType;
  sub.proc = (&sub_proc);
  mul.type = ProcedureType;
  mul.proc = (&mul_proc);
  div.type = ProcedureType;
  div.proc = (&div_proc);

  std::pair<Symbol, EnvResult> add_proce("+", add);
  std::pair<Symbol, EnvResult> sub_proce("-", sub);
  std::pair<Symbol, EnvResult> mul_proce("*", mul);
  std::pair<Symbol, EnvResult> div_proce("/", div);

  envmap.insert(add_proce);
  envmap.insert(sub_proce);
  envmap.insert(mul_proce);
  envmap.insert(div_proce);
}

void Environment::lognpowprocedures()
{
  EnvResult LogTen, power; //logarithmic and power procedures

  LogTen.type = ProcedureType;
  LogTen.proc = (&Log10_proc);
  power.type = ProcedureType;
  power.proc = (&pow_proc);

  std::pair<Symbol, EnvResult> LogTen_proce("log10", LogTen);
  std::pair<Symbol, EnvResult> power_proce("pow", power);

  envmap.insert(LogTen_proce);
  envmap.insert(power_proce);
}

void Environment::graphicprocedures()
{
  EnvResult point; // point - procedure
  EnvResult line;  // line - procedure
  EnvResult arc;   // arc - procedure

  point.type = ProcedureType;
  point.proc = (&point_proc);
  line.type = ProcedureType;
  line.proc = (&line_proc);
  arc.type = ProcedureType;
  arc.proc = (&arc_proc);

  std::pair<Symbol, EnvResult> point_proce("point", point);
  std::pair<Symbol, EnvResult> line_proce("line", line);
  std::pair<Symbol, EnvResult> arc_proce("arc", arc);

  envmap.insert(point_proce);
  envmap.insert(line_proce);
  envmap.insert(arc_proce);
}

void Environment::trigonometricprocedures()
{
  EnvResult sin, cos, arctan; // trigonometric procedures

  sin.type = ProcedureType;
  sin.proc = (&sin_proc);
  cos.type = ProcedureType;
  cos.proc = (&cos_proc);
  arctan.type = ProcedureType;
  arctan.proc = (&arctan_proc);

  std::pair<Symbol, EnvResult> sin_proce("sin", sin);
  std::pair<Symbol, EnvResult> cos_proce("cos", cos);
  std::pair<Symbol, EnvResult> arctan_proce("arctan", arctan);

  envmap.insert(sin_proce);
  envmap.insert(cos_proce);
  envmap.insert(arctan_proce);
}

void Environment::specialexpressions()
{
  EnvResult pi;
  Expression PI(atan2(0, -1));
  pi.type = ExpressionType;
  pi.exp = PI;
  std::pair<Symbol, EnvResult> pi_exp("pi", pi);
  envmap.insert(pi_exp);
}

Expression not_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. unary)
  if (args.size() > 2 || args.size() < 2)
  {
    throw InterpreterSemanticError("NOT is unary. Only single argument is required and allowed!");
  }
  // Ensure the type is appropriate for the arguments
  if (args[1].type != BooleanType)
  {
    throw InterpreterSemanticError("Invalid Type! NOT only works on Boolean arguments/atoms");
  }

  Expression result;

  result.head.type = BooleanType;

  // Logical Negation of the given argument:
  result.head.value.bool_value = !(args[1].value.bool_value);

  return result;
}

Expression and_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. m-ary)
  if (args.size() < 3)
  {
    throw InterpreterSemanticError("AND is m-ary. At least 2 arguments are required");
  }
  // Ensure the type is appropriate for the arguments
  if (args[1].type != BooleanType || args[2].type != BooleanType)
  {
    throw InterpreterSemanticError("Invalid Type! AND only works on Boolean arguments/atoms");
  }

  Expression result;

  result.head.type = BooleanType;

  result.head.value.bool_value = true;

  for (int i = 1; i < args.size(); i++)
  {
    // Logical conjunction of the given arguments:
    result.head.value.bool_value = (result.head.value.bool_value && args[i].value.bool_value);
  }

  return result;
}

Expression or_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. m-ary)
  if (args.size() < 3)
  {
    // Logical disjunction of the given arguments:
    throw InterpreterSemanticError("OR is m-ary. At least 2 arguments are required");
  }
  // Ensure the type is appropriate for the arguments
  for (int i = 1; i < args.size(); i++)
  {
    if (args[i].type != BooleanType)
    {
      throw InterpreterSemanticError("Invalid Type! OR only works on Boolean arguments/atoms");
    }
  }

  Expression result;

  result.head.type = BooleanType;

  result.head.value.bool_value = false;

  for (int i = 1; i < args.size(); i++)
  {
    // Logical disjunction of the given arguments:
    result.head.value.bool_value = (result.head.value.bool_value || args[i].value.bool_value);
  }

  return result;
}

Expression lessthan_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. binary)
  if (args.size() != 3)
  {
    throw InterpreterSemanticError("< is binary. 2 arguments are required");
  }
  // Ensure the type is appropriate for the arguments
  if (args[1].type != NumberType || args[2].type != NumberType)
  {
    throw InterpreterSemanticError("Invalid Type! < only works on Number arguments/atoms");
  }

  Expression result;

  result.head.type = BooleanType;

  // Less than comparison between two given arguments (in order)
  result.head.value.bool_value = (args[1].value.num_value < args[2].value.num_value);

  return result;
}

Expression lessthaneq_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. binary)
  if (args.size() != 3)
  {
    throw InterpreterSemanticError("<= is binary. Only 2 arguments are required");
  }
  // Ensure the type is appropriate for the arguments
  if (args[1].type != NumberType || args[2].type != NumberType)
  {
    throw InterpreterSemanticError("Invalid Type! <= only works on Number arguments/atoms");
  }

  Expression result;

  result.head.type = BooleanType;

  // Less than equal comparison between two given arguments (in order)
  result.head.value.bool_value = (args[1].value.num_value <= args[2].value.num_value);

  return result;
}

Expression greaterthan_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. binary)
  if (args.size() != 3)
  {
    throw InterpreterSemanticError("> is binary. Only 2 arguments are required");
  }
  // Ensure the type is appropriate for the arguments
  if (args[1].type != NumberType || args[2].type != NumberType)
  {
    throw InterpreterSemanticError("Invalid Type! > only works on Number arguments/atoms");
  }

  Expression result;

  result.head.type = BooleanType;

  // Greater than comparison between two given arguments (in order)
  result.head.value.bool_value = (args[1].value.num_value > args[2].value.num_value);

  return result;
}

Expression greaterthaneq_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. binary)
  if (args.size() != 3)
  {
    throw InterpreterSemanticError(">= is binary. Only 2 arguments are required");
  }
  // Ensure the type is appropriate for the arguments
  if (args[1].type != NumberType || args[2].type != NumberType)
  {
    throw InterpreterSemanticError("Invalid Type! >= only works on Number arguments/atoms");
  }

  Expression result;

  result.head.type = BooleanType;

  // Greater than equal comparison between two given arguments (in order)
  result.head.value.bool_value = (args[1].value.num_value >= args[2].value.num_value);

  return result;
}

Expression equal_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. binary)
  if (args.size() != 3)
  {
    throw InterpreterSemanticError("= is binary. Only 2 arguments are required");
  }
  // Ensure the type is appropriate for the arguments
  if (args[1].type != NumberType || args[2].type != NumberType)
  {
    throw InterpreterSemanticError("Invalid Type! = only works on Number arguments/atoms");
  }

  Expression result;

  result.head.type = BooleanType;

  // Equality comparison between two given arguments (in order)
  result.head.value.bool_value = (args[1].value.num_value == args[2].value.num_value);

  return result;
}

Expression add_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. m-ary)
  if (args.size() < 3)
  {
    throw InterpreterSemanticError("+ is m-ary. At least 2 arguments are required");
  }
  for (int i = 1; i < args.size(); i++)
  {
    // Ensure the type is appropriate for the arguments
    if (args[i].type != NumberType)
    {
      throw InterpreterSemanticError("Invalid Type! + only works on Number arguments/atoms");
    }
  }

  Expression Sum;

  Sum.head.type = NumberType;

  Sum.head.value.num_value = 0;

  for (int i = 1; i < args.size(); i++)
  {
    Sum.head.value.num_value = (Sum.head.value.num_value + args[i].value.num_value);
  }

  return Sum;
}

Expression sub_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. both binary (for subtraction) and unary (for negative representation))
  if (args.size() != 2 && args.size() != 3)
  {
    throw InterpreterSemanticError("- is either unary or binary. Either one or 2 arguments are required");
  }

  // Ensure the type is appropriate for the arguments
  if (args[1].type != NumberType && args[2].type != NumberType)
  {
    throw InterpreterSemanticError("Invalid Type! - only works on Number arguments/atoms");
  }

  Expression Diff;

  Diff.head.type = NumberType;

  if (args.size() == 2) //Negation (if single argument)
  {
    Diff.head.value.num_value = 0 - args[1].value.num_value;
  }
  else if (args.size() == 3) //Difference (if 2 arguments)
  {
    Diff.head.value.num_value = args[1].value.num_value - args[2].value.num_value;
  }

  return Diff;
}

Expression mul_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. m-ary)
  if (args.size() < 3)
  {
    throw InterpreterSemanticError("* is m-ary. At least 2 arguments are required");
  }

  for (int i = 1; i < args.size(); i++)
  {
    // Ensure the type is appropriate for the arguments
    if (args[i].type != NumberType)
    {
      throw InterpreterSemanticError("Invalid Type! * only works on Number arguments/atoms");
    }
  }

  Expression Prod;

  Prod.head.type = NumberType;

  Prod.head.value.num_value = 1;

  for (int i = 1; i < args.size(); i++)
  {
    Prod.head.value.num_value = (Prod.head.value.num_value * args[i].value.num_value);
  }

  return Prod;
}

Expression div_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. binary)
  if (args.size() != 3)
  {
    throw InterpreterSemanticError("/ is binary. 2 arguments are required");
  }
  // Ensure the type is appropriate for the arguments
  if (args[1].type != NumberType || args[2].type != NumberType)
  {
    throw InterpreterSemanticError("Invalid Type! / only works on Number arguments/atoms");
  }

  Expression Quotient;

  Quotient.head.type = NumberType;

  Quotient.head.value.num_value = (args[1].value.num_value / args[2].value.num_value);

  return Quotient;
}

Expression Log10_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. unary)
  if (args.size() != 2)
  {
    throw InterpreterSemanticError("Error (semantic). log10 is unary. Just 1 argument is required");
  }

  // Ensure the type is appropriate for the arguments
  if (args[1].type != NumberType)
  {
    throw InterpreterSemanticError("Error (semantic). Invalid Type! log10 only works on Number arguments/atoms");
  }

  Expression Result;

  Result.head.type = NumberType;

  // Logarithmic function (base 10) applied on the given argument
  Result.head.value.num_value = log10(args[1].value.num_value);

  return Result;
}

Expression pow_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. binary)
  if (args.size() != 3)
  {
    throw InterpreterSemanticError("Error (semantic). power is binary. Only 2 arguments are required");
  }

  // Ensure the type is appropriate for the arguments
  if (args[1].type != NumberType || args[2].type != NumberType)
  {
    throw InterpreterSemanticError("Error (semantic). Invalid Type! power only works on Number arguments/atoms");
  }

  Expression Result;

  Result.head.type = NumberType;

  // Power function applied on the given argument (with the base as the first argument)
  Result.head.value.num_value = pow(args[1].value.num_value, args[2].value.num_value);

  return Result;
}

Expression point_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. binary)
  if (args.size() != 3)
  {
    throw InterpreterSemanticError("Error (semantic). point is binary. Only 2 arguments are required");
  }

  // Ensure the type is appropriate for the arguments
  if (args[1].type != NumberType || args[2].type != NumberType)
  {
    throw InterpreterSemanticError("Error (semantic). Invalid Type! point only works on Number arguments/atoms");
  }

  Expression Result;

  Result.head.type = PointType;
  // Assigning the coordinates for the point (x, y):
  Result.head.value.point_value.x = args[1].value.num_value;
  Result.head.value.point_value.y = args[2].value.num_value;

  return Result;
}

Expression line_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. binary)
  if (args.size() != 3)
  {
    throw InterpreterSemanticError("Error (semantic). line is binary. Only 2 arguments are required");
  }

  // Ensure the type is appropriate for the arguments
  if (args[1].type != PointType || args[2].type != PointType)
  {
    throw InterpreterSemanticError("Error (semantic). Invalid Type! line only works on Number arguments/atoms");
  }

  Expression Result;

  Result.head.type = LineType;

  // Creating a line with the given 2 points:

  Result.head.value.line_value.first.x = args[1].value.point_value.x;
  Result.head.value.line_value.first.y = args[1].value.point_value.y;
  Result.head.value.line_value.second.x = args[2].value.point_value.x;
  Result.head.value.line_value.second.y = args[2].value.point_value.y;

  return Result;
}

Expression arc_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. tertiary)
  if (args.size() != 4)
  {
    throw InterpreterSemanticError("Error (semantic). arc is tertiary. Only 3 arguments are required");
  }

  // Ensure the type is appropriate for the arguments
  if (args[1].type != PointType || args[2].type != PointType || args[3].type != NumberType)
  {
    throw InterpreterSemanticError("Error (semantic). Invalid Type! arc only works on Number arguments/atoms");
  }

  Expression Result;

  Result.head.type = ArcType;

  // Creating an arc:

  Result.head.value.arc_value.center.x = args[1].value.point_value.x;
  Result.head.value.arc_value.center.y = args[1].value.point_value.y;
  Result.head.value.arc_value.start.x = args[2].value.point_value.x;
  Result.head.value.arc_value.start.y = args[2].value.point_value.y;
  Result.head.value.arc_value.span = args[3].value.num_value;

  return Result;
}

Expression sin_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. unary)
  if (args.size() != 2)
  {
    throw InterpreterSemanticError("Error (semantic). sin is unary. Only 1 argument is required");
  }

  // Ensure the type is appropriate for the arguments
  if (args[1].type != NumberType)
  {
    throw InterpreterSemanticError("Error (semantic). Invalid Type! sin only works on Number arguments/atoms");
  }

  Expression Result;

  Result.head.type = NumberType;
  Result.head.value.num_value = sin(args[1].value.num_value);

  return Result;
}

Expression cos_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. unary)
  if (args.size() != 2)
  {
    throw InterpreterSemanticError("Error (semantic). cos is unary. Only 1 argument is required");
  }

  // Ensure the type is appropriate for the arguments
  if (args[1].type != NumberType)
  {
    throw InterpreterSemanticError("Error (semantic). Invalid Type! cos only works on Number arguments/atoms");
  }

  Expression Result;

  Result.head.type = NumberType;
  Result.head.value.num_value = cos(args[1].value.num_value);

  return Result;
}

Expression arctan_proc(const std::vector<Atom> &args)
{
  // Ensure the arity is followed (i.e. binary)
  if (args.size() != 3)
  {
    throw InterpreterSemanticError("Error (semantic). arctan is unary. Only 2 arguments are required");
  }

  // Ensure the type is appropriate for the arguments
  if (args[1].type != NumberType || args[2].type != NumberType)
  {
    throw InterpreterSemanticError("Error (semantic). Invalid Type! cos only works on Number arguments/atoms");
  }

  Expression Result;

  Result.head.type = NumberType;
  Result.head.value.num_value = atan2(args[1].value.num_value, args[2].value.num_value);

  return Result;
}

// Returns an existing mapping for a procedure
Procedure Environment::searchProc(Symbol x)
{
  std::map<Symbol, EnvResult>::iterator it;

  it = envmap.find(x);

  if (it == envmap.end())
  {
    throw InterpreterSemanticError("Error (semantic). It exists as you're accessing a procedure that should not exist.");
  }

  return it->second.proc;
}

// Returns an existing mapping for an expression
Expression Environment::searchExp(Symbol pi)
{
  std::map<Symbol, EnvResult>::iterator it;

  it = envmap.find(pi);

  if (it == envmap.end())
  {
    throw InterpreterSemanticError("Error (semantic). It exists as you're accessing a symbol that has no active mapping in the environment!");
  }
  return it->second.exp;
}

void Environment::insertexp(Symbol x, Expression y)
{
  EnvResult X;
  X.exp = y;
  envmap.insert(std::pair<Symbol, EnvResult>(x, X));
}

void Environment::insertproc(Symbol x, Procedure y)
{
  EnvResult X;
  X.proc = y;
  X.type = ProcedureType;

  envmap.insert(std::pair<Symbol, EnvResult>(x, X));
}