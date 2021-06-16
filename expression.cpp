#include "expression.hpp"

// system includes
#include <sstream>
#include <cmath>
#include <limits>
#include <cctype>
#include <tuple>
#include <iostream>

Expression::Expression(bool tf)
{
  // HEAD (Atom):
  head.type = BooleanType;

  head.value.bool_value = tf;
}

Expression::Expression(double num)
{
  // HEAD (Atom):
  head.type = NumberType;
  head.value.num_value = num;
}

Expression::Expression(const std::string &sym)
{
  // HEAD (Atom):
  head.type = SymbolType;
  head.value.sym_value = sym;
}

Expression::Expression(std::tuple<double, double> value)
{
  head.type = PointType;
  head.value.point_value.x = std::get<0>(value);
  head.value.point_value.y = std::get<1>(value);
}

Expression::Expression(std::tuple<double, double> start,
                       std::tuple<double, double> end)
{
  head.type = LineType;
  head.value.line_value.first.x = std::get<0>(start);
  head.value.line_value.first.y = std::get<1>(start);
  head.value.line_value.second.x = std::get<0>(end);
  head.value.line_value.second.y = std::get<1>(end);
}

Expression::Expression(std::tuple<double, double> center,
                       std::tuple<double, double> start,
                       double angle)
{
  head.type = ArcType;
  head.value.arc_value.center.x = std::get<0>(center);
  head.value.arc_value.center.y = std::get<1>(center);
  head.value.arc_value.start.x = std::get<0>(start);
  head.value.arc_value.start.y = std::get<1>(start);
  head.value.arc_value.span = angle;
}

bool Expression::operator==(const Expression &exp) const noexcept
{
  bool flag = false;
  if (head.type == exp.head.type)
  {
    switch (head.type)
    {
    case NoneType:
      flag = true;
      break;
    case BooleanType:
      if (head.value.bool_value == exp.head.value.bool_value)
      {
        flag = true;
      }
      break;
    case NumberType:
      if (fabs(head.value.num_value - exp.head.value.num_value) < std::numeric_limits<double>::epsilon())
      {
        flag = true;
      }
      break;
    case ListType:
      if (head.value.sym_value == exp.head.value.sym_value)
      {
        flag = true;
      }
      break;
    case SymbolType:
      if (head.value.sym_value == exp.head.value.sym_value)
      {
        flag = true;
      }
      break;
    case PointType:
      if (head.value.point_value.x == exp.head.value.point_value.x && head.value.point_value.y == exp.head.value.point_value.y)
      {
        flag = true;
      }
      break;
    case LineType:
      // if (head.value.line_value.first.x == exp.head.value.line_value.first.x && head.value.line_value.first.y == exp.head.value.line_value.first.y && head.value.line_value.second.x == exp.head.value.line_value.second.x && head.value.line_value.second.y == exp.head.value.line_value.second.y)
      if (head.value.line_value.first == exp.head.value.line_value.first && head.value.line_value.second == exp.head.value.line_value.second)
      {
        flag = true;
      }
      break;
    case ArcType:
      if (head.value.arc_value.center.x == exp.head.value.arc_value.center.x && head.value.arc_value.center.y == exp.head.value.arc_value.center.y && head.value.arc_value.start.x == exp.head.value.arc_value.start.x && head.value.arc_value.start.y == exp.head.value.arc_value.start.y && head.value.arc_value.span == exp.head.value.arc_value.span)
      {
        flag = true;
      }
      break;
    };
  }
  return flag;
}

bool Expression::operator!=(const Expression &exp) const noexcept
{
  bool flag = true;
  if (head.type == exp.head.type)
  {
    switch (head.type)
    {
    case NoneType:
      flag = false;
      break;
    case BooleanType:
      if (head.value.bool_value == exp.head.value.bool_value)
      {
        flag = false;
      }
      break;
    case NumberType:
      if (fabs(head.value.num_value - exp.head.value.num_value) < std::numeric_limits<double>::epsilon())
      {
        flag = false;
      }
      break;
    case ListType:
      if (head.value.sym_value == exp.head.value.sym_value)
      {
        flag = false;
      }
      break;
    case SymbolType:
      if (head.value.sym_value == exp.head.value.sym_value)
      {
        flag = false;
      }
      break;
    case PointType:
      if (head.value.point_value.x == exp.head.value.point_value.x && head.value.point_value.y == exp.head.value.point_value.y)
      {
        flag = false;
      }
      break;
    case LineType:
      // if (head.value.line_value.first.x == exp.head.value.line_value.first.x && head.value.line_value.first.y == exp.head.value.line_value.first.y && head.value.line_value.second.x == exp.head.value.line_value.second.x && head.value.line_value.second.y == exp.head.value.line_value.second.y)
      if (head.value.line_value.first == exp.head.value.line_value.first && head.value.line_value.second == exp.head.value.line_value.second)
      {
        flag = false;
      }
      break;
    case ArcType:
      if (head.value.arc_value.center.x == exp.head.value.arc_value.center.x && head.value.arc_value.center.y == exp.head.value.arc_value.center.y && head.value.arc_value.start.x == exp.head.value.arc_value.start.x && head.value.arc_value.start.y == exp.head.value.arc_value.start.y && head.value.arc_value.span == exp.head.value.arc_value.span)
      {
        flag = false;
      }
      break;
    };
  }
  return flag;
}

std::ostream &operator<<(std::ostream &out, const Expression &exp)
{
  // TODO: implement this function
}

bool token_to_atom(const std::string &token, Atom &atom)
{
  // return true if a token is valid. otherwise, return false.

  int len = token.length();

  bool is_num = false;
  bool is_sym = false;
  bool is_bool = false;
  bool is_none = false;
  bool is_list = false;
  bool is_bracket = false;

  // check if the token is a valid list, none type or invalid bracket type:
  bool checkrest = checktoken(atom, token, is_num, is_sym, is_bool, is_none, is_list, is_bracket);

  // check if it is a valid boolean, number or symbol type token
  if (!is_bracket && checkrest)
  {
    checkBooleanAtom(atom, token, is_bool, checkrest);

    if (checkrest) //check if it is a number or symbol type token
    {
      checkNumberAtom(atom, token, is_num, checkrest);

      //check if the given token is of symbol type
      if (checkrest)
      {
        checkSymbolAtom(atom, token, is_sym, checkrest);
      }
    }
  }

  // Return if the token is valid.
  // The token is valid if it is either a bool, symbol, number, none or list type AND it is NOT a bracket/parenthesis.
  return ((is_bool || is_sym || is_num || is_none || is_list) && !is_bracket);
}

bool checktoken(Atom &atom, std::string token, bool &is_num, bool &is_sym, bool &is_bool, bool &is_none, bool &is_list, bool &is_bracket)
{
  bool checkrest = true;

  // Brackets/Parentheses (note: they are not valid tokens)
  checkparentheses(atom, token, is_bracket, checkrest);

  // Arithmetic, Relational and Logical Operators:
  checkoperators(atom, token, is_none, is_list, checkrest);

  // Logarithmic/Exponential, Graphical and Trigonometric functions respectively:
  checkfunctions(atom, token, is_none, is_list, checkrest);

  // Special forms and invalid special characters:
  specialcases(atom, token, is_none, is_list, checkrest);

  return checkrest;
}

void checkparentheses(Atom &atom, std::string token, bool &is_bracket, bool &checkrest)
{
  if (token == "(" || token == ")" || token == "[" || token == "]")
  {
    is_bracket = true;
    checkrest = false;
  }
}

void checkoperators(Atom &atom, std::string token, bool &is_none, bool &is_list, bool &checkrest)
{
  if (checkrest)
  {
    if (token == "-" || token == "+" || token == "*" || token == "/")
    {
      atom.type = ListType;
      atom.value.sym_value = token;
      is_list = true;
      checkrest = false;
    }
    else if (token == ">" || token == ">=" || token == "<" || token == "<=" || token == "=")
    {
      atom.type = NoneType;
      atom.value.sym_value = token;
      is_none = true;
      checkrest = false;
    }
    else if (token == "not" || token == "and" || token == "or")
    {
      atom.type = NoneType;
      atom.value.sym_value = token;
      is_none = true;
      checkrest = false;
    }
  }
}

void checkfunctions(Atom &atom, std::string token, bool &is_none, bool &is_list, bool &checkrest)
{
  if (checkrest)
  {
    if (token == "log10" || token == "pow")
    {
      atom.type = NoneType;
      atom.value.sym_value = token;
      is_none = true;
      checkrest = false;
    }
    else if (token == "line" || token == "point" || token == "arc")
    {
      atom.type = NoneType;
      atom.value.sym_value = token;
      is_none = true;
      checkrest = false;
    }
    else if (token == "sin" || token == "cos" || token == "arctan")
    {
      atom.type = NoneType;
      atom.value.sym_value = token;
      is_none = true;
      checkrest = false;
    }
  }
}

void specialcases(Atom &atom, std::string token, bool &is_none, bool &is_list, bool &checkrest)
{
  if (checkrest)
  {
    // Special forms/keywords:
    if (token == "define" || token == "if" || token == "begin" || token == "draw")
    {
      atom.type = ListType;
      atom.value.sym_value = token;
      is_list = true;
      checkrest = false;
    }
    // Illegal special characters for expression evaluations
    else if (token == "@" || token == "!" || token == "#" || token == "$" || token == "%" || token == "^" || token == "&")
    {
      atom.type = NoneType;
      atom.value.sym_value = token;
      is_none = true;
      checkrest = false;
    }
  }
}

void checkBooleanAtom(Atom &atom, std::string token, bool &is_bool, bool &checkrest)
{
  int len = token.length();

  //Check if token is possibly a boolean value
  std::string check_bool = token;
  for (int i = 0; i < len; i++)
  {
    if (bool(isalpha(check_bool[i])))
    {
      check_bool[i] = tolower(check_bool[i]); // Avoids case sensitivity. Example: True, TRUE or true are treated the same.
    }
    else //if an invalid character exists within the token, break because it definitely not a boolean value of true/false
    {
      break;
    }
  }

  checkrest = false;

  if (check_bool == "true")
  {
    atom.type = BooleanType;
    atom.value.bool_value = true;
    is_bool = true;
  }
  else if (check_bool == "false")
  {
    atom.type = BooleanType;
    atom.value.bool_value = false;
    is_bool = true;
  }
  else
  {
    checkrest = true;
  }
}

void checkNumberAtom(Atom &atom, std::string token, bool &is_num, bool &checkrest)
{
  int len = token.length();

  //Check if token is possibly a number value
  if (bool(isdigit(token[0])) || token.substr(0, 1) == "-")
  {
    bool single_e = false; // flag to check if an exponent e is encountered within a token
    bool one_decpoint = false;
    int num_val;
    for (int i = 0; i < len; i++)
    {
      if (bool(isdigit(token[i])) || token.substr(i, 1) == ".")
      {
        is_num = true;
        if (!one_decpoint && token.substr(i, 1) == ".")
        {
          one_decpoint = true; // it's a decimal number
        }
        else if (one_decpoint && token.substr(i, 1) == ".")
        {
          is_num = false;
          break; //break because invalid case -- multiple decimal points were encountered
        }
      }
      else if (bool(isalpha(token[i])))
      {
        if (token.substr(i, 1) == "e" && !single_e)
        {
          is_num = true;
          single_e = true;
        }
        else if ((token.substr(i, 1) == "e" && single_e) || (token.substr(i, 1) != "e"))
        {
          is_num = false;
          break;
        }
      }
    }

    if (is_num)
    {
      num_val = std::stoi(token);
      atom.type = NumberType;
      atom.value.num_value = num_val;
      checkrest = false;
    }
    else
    {
      checkrest = true;
    }
  }
  else
  {
    checkrest = true;
  }
}

void checkSymbolAtom(Atom &atom, std::string token, bool &is_sym, bool &checkrest)
{
  int len = token.length();

  for (int i = 0; i < len; i++)
  {
    // if there is no space or digit as the first character, it is assumed to be a symbol.
    // Note: the invalid special characters were dealt with at the top of this function.
    // Thus, we're only checking if any of the characters are spaces, and the first token is not a digit.

    if (!bool(isspace(token[i])) && !bool(isdigit(token[0])))
    {
      is_sym = true;
    }
  }

  atom.type = SymbolType;
  atom.value.sym_value = token;
}