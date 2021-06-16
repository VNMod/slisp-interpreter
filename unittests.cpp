#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "expression.hpp"
#include "interpreter.hpp"
#include "tokenize.hpp"
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"

TEST_CASE("Testing some semantically correct expressions (that haven't already been checked)", "[interpreter]")
{
    std::vector<std::string> programs1 = {
        "(log10 10)",
        "(pow 2 3)",
    };

    Interpreter interp1;
    Interpreter interp2;

    std::istringstream iss1(programs1[0]);
    std::istringstream iss2(programs1[1]);

    bool ok1 = interp1.parse(iss1);
    bool ok2 = interp2.parse(iss2);

    Atom atom1, atom2;
    atom1.type = NumberType;
    atom2.type = NumberType;
    atom1.value.num_value = 1;
    atom2.value.num_value = 8;

    Expression Logten(atom1.value.num_value);
    Expression Power(atom2.value.num_value);

    REQUIRE(interp1.eval() == Logten);
    REQUIRE(interp2.eval() == Power);
}

TEST_CASE("Testing semantically incorrect expressions (that haven't been checked yet) 1", "[interpreter]")
{
    std::vector<std::string> programs1 = {
        "(< True False)",         // incorrect argument type. only numbers accepted so can't compare between bool values.
        "(<= True False)",        // incorrect argument type. only numbers accepted so can't compare between bool values.
        "(> True False)",         // incorrect argument type. only numbers accepted so can't compare between bool values.
        "(>= True False)",        // incorrect argument type. only numbers accepted so can't compare between bool values.
        "(= True False)",         // incorrect argument type. only numbers accepted so can't check for equality between bool values.
        "(+ True False)",         // incorrect argument type. only numbers accepted so can't add bool values.
        "(- True False)",         // incorrect argument type. only numbers accepted so can't subtract bool values.
        "(* True False)",         // incorrect argument type. only numbers accepted so can't divide bool values.
        "(/ 1 True)",             // incorrect argument type. only number accepted
        "(not True False)",       // too many arguments (in not)
        "(not 1)",                // incorrect argument type. only boolean accepted
        "(and True)",             // too few arguments (in and)
        "(and 1 2)",              // incorrect argument type. only boolean accepted
        "(or True)",              // too few arguments (in or)
        "(or 1 2)",               // incorrect argument type. only boolean accepted
        "(< 1 2 3)",              // too many arguments (in <)
        "(< 1)",                  // too few arguments (in <)
        "(<= 1 2 3)",             // too many arguments (in <=)
        "(<= 1)",                 // too few arguments (in <=)
        "(> 1 2 3)",              // too many arguments (in >)
        "(> 1)",                  // too few arguments (in >)
        "(>= 1 2 3)",             // too many arguments (in >=)
        "(>= 1)",                 // too few arguments (in >=)
        "(= 1 2 3)",              // too many arguments (in =)
        "(= 1)",                  // too few arguments (in =)
        "(+ 1)",                  // too few arguments (in +)
        "(- 1 2 3)",              // too many arguments (in -)
        "(/ 1 2 3)",              // too many arguments (in /)
        "(* 1)",                  // too few arguments (in *)
        "(define a 1 2)",         // too many arguments (in define)
        "(define 1 2)",           // incorrect argument type. argument 2 or args[1] must be a symbol
        "(define begin 1)",       // begin is a keyword that cannot be used as a symbol for argument 2
        "(if tuer 4)",            // incorrect argument type. argument 2 or args[1] must evaluate to a boolean True/False
        "(if True (4) (-4) (5))", // too many arguments
        "(if 4 (4) (-4) (5))",    // incorrect argument type. argument 2 or args[1] must evaluate to a boolean True/False
        "(define (#) ($))",       // special characters such as # or $ cannot be used as a symbol
        "(define define 2)",      // incorrect argument type. argument 2 or args[1] cannot be a keyword such as define
    };

    for (auto s : programs1)
    {
        Interpreter interp;

        std::istringstream iss(s);

        bool ok = interp.parse(iss);

        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
}

TEST_CASE("Testing semantically incorrect expressions (that haven't been checked yet) 2", "[interpreter]")
{
    std::vector<std::string> programs1 = {
        "(draw)",      // too few arguments (for draw since it's m-ary)
        "(log10)",     // too few arguments (for log10 since it's unary)
        "(log10 x)",   //incorrect argument type. argument 2 or args[1] must be of type Number
        "(pow)",       // too few arguments (for log10 since it's binary)
        "(pow x y)",   //incorrect argument type. argument 2 and 3 or args[1] and args[2] must be of type Number
        "(point)",     // too few arguments (for point since it's binary)
        "(point x)",   //incorrect argument type. argument 2 or args[1] must be of type Number
        "(line)",      // too few arguments (for line since it's binary)
        "(line x y)",  //incorrect argument type. argument 2, 3 or args[1] and args[2] must be of type Point
        "(arc)",       // too few arguments (for line since it's tertiary)
        "(arc x)",     //incorrect argument type.
        "(arc 1 2 3)", //incorrect argument types. argument 2, 3 and 4 or args[1], args[2] and args[3] must be of type Point, Point and Number respectively.
        "(point a b)", //incorrect argument types. argument 2 and 3 or args[1] and args[2] must be of type Point, Point respectively.
    };

    std::vector<std::string> programs2 = {
        "()1)",      // invalid argument -- syntax error due to invalid expression
        "))(1 and)", // invalid argument
    };

    for (auto s : programs1)
    {
        Interpreter interp;

        std::istringstream iss(s);

        bool ok = interp.parse(iss);

        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }

    for (auto s : programs2)
    {
        Interpreter interp;

        std::istringstream iss(s);

        bool ok = interp.parse(iss);

        REQUIRE_FALSE(ok);
    }
}

TEST_CASE("Testing certain methods within the environment (also for coverage testing)", "[Environment]")
{
    std::string exp = "(define a 1)";
    std::istringstream replprog(exp);

    Interpreter interp;

    bool ok = interp.parse(replprog);

    Expression result;

    result = interp.eval();

    // to check if the mapping was appropriately updated in the environment:

    Expression check_exp = interp.returnenv().searchExp("a");

    REQUIRE(check_exp.head.type == NumberType);
    REQUIRE(check_exp.head.value.num_value == 1);

    interp.resetenv(); // now, reset the environment

    // and check if the mapping still exists in the environment:

    REQUIRE_THROWS_AS(interp.returnenv().searchExp("a"), InterpreterSemanticError);
}

TEST_CASE("Test Type Inference 2", "[types]")
{

    Atom a;

    std::string token;

    token = "]";
    REQUIRE_FALSE(token_to_atom(token, a));

    token = ")";
    REQUIRE_FALSE(token_to_atom(token, a));
}

TEST_CASE("Test Expression Constructors 2", "[types]")
{

    // Expression exp1;

    // REQUIRE(exp1 == Expression());

    //testing default constructor
    Expression exp1;
    Expression exp2;

    // testing operator overloading == for none type expression
    REQUIRE(exp1 == exp2);

    Symbol s = "hello";

    // testing parameterized symbol type constructors
    Expression exp3(s);
    Expression exp4(s);

    // testing operator overloading == for symbol type expression
    REQUIRE(exp3 == exp4);

    Boolean x = true;

    // testing parameterized boolean constructors
    Expression exp5(x);
    Expression exp6(x);

    // testing operator overloading == for boolean type expression
    REQUIRE(exp5 == exp6);

    Number y = 3.14;

    // testing parameterized number constructors
    Expression exp7(y);
    Expression exp8(y);

    // testing operator overloading == for number type expression
    REQUIRE(exp7 == exp8);

    Expression exp9;
    exp9.head.type = ListType;
    exp9.head.value.sym_value = "+";

    // testing operator overloading == for list type expression
    REQUIRE(exp9 == exp9);

    Atom atom;
    atom.type = NumberType;
    atom.value.num_value = 2.2;

    Expression exp11;
    exp11.head.type = NumberType;
    exp11.head.value.num_value = 2.3;

    REQUIRE_FALSE(exp9 == exp11);

    // Testing the parametrized constructor with a parameter of type Atom
    Expression exp10(atom);
}

TEST_CASE("Testing token_to_atom", "[tokenize]")
{
    std::string program1 = "(0.5.10)"; //multiple decimal points
    std::string program2 = "1ee1";     //multiple es
    std::string program3 = "13.2";     //multiple es
    std::string program4 = "log10";

    std::istringstream iss1(program1);
    std::istringstream iss2(program2);
    std::istringstream iss3(program3);
    std::istringstream iss4(program4);

    Atom atom;

    TokenSequenceType tokens1 = tokenize(iss1);
    TokenSequenceType tokens2 = tokenize(iss2);
    TokenSequenceType tokens3 = tokenize(iss3);
    TokenSequenceType tokens4 = tokenize(iss4);

    for (int i = 0; i < tokens1.size(); i++)
    {
        if (tokens1[i] != "(" && tokens1[i] != ")")
        {
            REQUIRE_FALSE(token_to_atom(tokens1[i], atom));
        }
    }

    for (int i = 0; i < tokens2.size(); i++)
    {
        REQUIRE_FALSE(token_to_atom(tokens2[i], atom));
    }

    REQUIRE(token_to_atom(tokens3[0], atom));

    REQUIRE(token_to_atom(tokens4[0], atom));
}

TEST_CASE("Testing != operator overloader", "[expression]")
{
    bool truth = true;
    Expression exp1(truth), exp2(truth);
    REQUIRE_FALSE(exp1 != exp2);

    std::string sym = "hi";
    Expression exp3(sym), exp4(sym);
    REQUIRE_FALSE(exp3 != exp4);

    double a = 3.4;
    Expression exp5(a), exp6(a);
    REQUIRE_FALSE(exp5 != exp6);

    Expression list;
    list.head.type = ListType;
    list.head.value.sym_value = "list";

    Expression exp7 = list;
    Expression exp8 = list;
    REQUIRE_FALSE(exp7 != exp8);

    Expression point;
    point.head.type = PointType;
    point.head.value.point_value.x = 5;
    point.head.value.point_value.y = 5;

    Expression exp9 = point;
    Expression exp10 = point;

    REQUIRE_FALSE(exp9 != exp10);

    Expression line;
    line.head.type = LineType;
    line.head.value.line_value.first.x = 5;
    line.head.value.line_value.first.y = 5;

    line.head.value.line_value.second.x = 6;
    line.head.value.line_value.second.y = 6;

    Expression exp11 = line;
    Expression exp12 = line;

    REQUIRE_FALSE(exp11 != exp12);

    Expression arc, center, start, span;
    arc.head.type = ArcType;
    arc.head.value.arc_value.span = 5;

    arc.head.value.arc_value.center.x = 3;
    arc.head.value.arc_value.center.y = 5;

    arc.head.value.arc_value.start.x = 1;
    arc.head.value.arc_value.start.y = 1;

    Expression exp13 = arc, exp14 = arc;

    REQUIRE_FALSE(exp13 != exp14);
}