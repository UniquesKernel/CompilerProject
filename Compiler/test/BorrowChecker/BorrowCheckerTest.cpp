#include "Visitors/borrowChecker.hpp"
#include "Expressions/ReturnExpression.hpp"
#include "Expressions/baseExpression.hpp"
#include "Expressions/blockExpression.hpp"
#include "Expressions/functionCall.hpp"
#include "Expressions/functionDeclaration.hpp"
#include "Expressions/programExpression.hpp"
#include "Expressions/referenceAssignmentExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Expressions/variableExpression.hpp"
#include "Visitors/baseVisitor.hpp"
#include <catch2/catch.hpp>
#include <stdexcept>
#include <vector>

using ArgumentList = std::vector<std::pair<std::string, std::string>>;
using InstructionList = std::vector<BaseExpression *>;
using ProgramFunctions = std::vector<FunctionDeclaration *>;

void setupProgram() {}

TEST_CASE("BorrowChecker", "[Assignment]") {
  SECTION("Empty Main Program") {
    /*
     *  fn main(): int {
     *    return 0;
     *  }
     * */
    InstructionList instructionList = InstructionList();
    TerminalExpression *returnExpression = new TerminalExpression(0);

    instructionList.push_back(returnExpression);
    BlockExpression *programInstructionList =
        new BlockExpression(instructionList);

    ArgumentList args = ArgumentList();

    FunctionDeclaration *mainFunction =
        new FunctionDeclaration("main", "int", programInstructionList);

    ProgramFunctions functionList = ProgramFunctions();
    functionList.push_back(mainFunction);

    ProgramExpression program = ProgramExpression(functionList);

    BorrowChecker *borrowChecker = new BorrowChecker();

    REQUIRE_NOTHROW(program.accept(borrowChecker));

    delete borrowChecker;
  }

  SECTION("Main Program With 1 assignment", "[Assignment]") {
    /*
     *  fn main(): int {
     *    let x: int = 0;
     *    return 0;
     *  }
     * */
    InstructionList instructionList = InstructionList();

    // Program Instructins
    VariableAssignmentExpression *assignment = new VariableAssignmentExpression(
        new TerminalExpression(0), new VariableExpression("x"), false, "int");
    ReturnExpression *returnExpression =
        new ReturnExpression(new TerminalExpression(0));

    // adding them to main function declaration together with argument list
    instructionList.push_back(assignment);
    instructionList.push_back(returnExpression);
    BlockExpression *programInstructionList =
        new BlockExpression(instructionList);
    ArgumentList args = ArgumentList();
    FunctionDeclaration *mainFunction =
        new FunctionDeclaration("main", "int", programInstructionList);

    // Create Program from list of available functions i.e. AST
    ProgramFunctions functionList = ProgramFunctions();
    functionList.push_back(mainFunction);
    ProgramExpression program = ProgramExpression(functionList);

    // initialize BorrowChecker
    BorrowChecker *borrowChecker = new BorrowChecker();

    // Assert
    REQUIRE_NOTHROW(program.accept(borrowChecker));

    // clean up
    delete borrowChecker;
  }

  SECTION("main Program with 1 immutable reference assignment",
          "[assignment]") {
    /*
     *  fn main(): int {
     *    let x: int = 0;
     *    let y: &int = &x;
     *    return 0;
     *  }
     * */
    InstructionList instructionList = InstructionList();

    // Program Instructins
    VariableAssignmentExpression *assignment = new VariableAssignmentExpression(
        new TerminalExpression(0), new VariableExpression("x"), false, "int");
    ReturnExpression *returnExpression =
        new ReturnExpression(new TerminalExpression(0));
    ReferenceAssignmentExpression *referenceAssignmentExpression =
        new ReferenceAssignmentExpression("y", "x", "&int", false);

    // adding them to main function declaration together with argument list
    instructionList.push_back(assignment);
    instructionList.push_back(referenceAssignmentExpression);
    instructionList.push_back(returnExpression);
    BlockExpression *programInstructionList =
        new BlockExpression(instructionList);
    ArgumentList args = ArgumentList();
    FunctionDeclaration *mainFunction =
        new FunctionDeclaration("main", "int", programInstructionList);

    // Create Program from list of available functions i.e. AST
    ProgramFunctions functionList = ProgramFunctions();
    functionList.push_back(mainFunction);
    ProgramExpression program = ProgramExpression(functionList);

    // initialize BorrowChecker
    BorrowChecker *borrowChecker = new BorrowChecker();

    // Assert
    REQUIRE_NOTHROW(program.accept(borrowChecker));

    // clean up
    delete borrowChecker;
  }

  SECTION("main Program with 3 immutable reference assignment",
          "[assignment]") {
    /*
     *  fn main(): int {
     *    let x: int = 0;
     *    let a: &int = &x;
     *    let b: &int = &x;
     *    let c: &int = &x;
     *    return 0;
     *  }
     * */
    InstructionList instructionList = InstructionList();

    // Program Instructins
    VariableAssignmentExpression *assignment = new VariableAssignmentExpression(
        new TerminalExpression(0), new VariableExpression("x"), false, "int");
    ReturnExpression *returnExpression =
        new ReturnExpression(new TerminalExpression(0));
    ReferenceAssignmentExpression *referenceA =
        new ReferenceAssignmentExpression("a", "x", "&int", false);
    ReferenceAssignmentExpression *referenceB =
        new ReferenceAssignmentExpression("b", "x", "&int", false);
    ReferenceAssignmentExpression *referenceC =
        new ReferenceAssignmentExpression("c", "x", "&int", false);

    // adding them to main function declaration together with argument list
    instructionList.push_back(assignment);
    instructionList.push_back(referenceA);
    instructionList.push_back(referenceB);
    instructionList.push_back(referenceC);
    instructionList.push_back(returnExpression);
    BlockExpression *programInstructionList =
        new BlockExpression(instructionList);
    ArgumentList args = ArgumentList();
    FunctionDeclaration *mainFunction =
        new FunctionDeclaration("main", "int", programInstructionList);

    // Create Program from list of available functions i.e. AST
    ProgramFunctions functionList = ProgramFunctions();
    functionList.push_back(mainFunction);
    ProgramExpression program = ProgramExpression(functionList);

    // initialize BorrowChecker
    BorrowChecker *borrowChecker = new BorrowChecker();

    // Assert
    REQUIRE_NOTHROW(program.accept(borrowChecker));

    // clean up
    delete borrowChecker;
  }

  SECTION("main Program with 1 mutable reference assignment", "[assignment]") {
    /*
     *  fn main(): int {
     *    let mut x: int = 0;
     *    let y: &int = &mut x;
     *    return 0;
     *  }
     * */
    InstructionList instructionList = InstructionList();

    // Program Instructins
    VariableAssignmentExpression *assignment = new VariableAssignmentExpression(
        new TerminalExpression(0), new VariableExpression("x"), true, "int");
    ReturnExpression *returnExpression =
        new ReturnExpression(new TerminalExpression(0));
    ReferenceAssignmentExpression *referenceY =
        new ReferenceAssignmentExpression("y", "x", "&int", true);

    // adding them to main function declaration together with argument list
    instructionList.push_back(assignment);
    instructionList.push_back(referenceY);
    instructionList.push_back(returnExpression);
    BlockExpression *programInstructionList =
        new BlockExpression(instructionList);
    ArgumentList args = ArgumentList();
    FunctionDeclaration *mainFunction =
        new FunctionDeclaration("main", "int", programInstructionList);

    // Create Program from list of available functions i.e. AST
    ProgramFunctions functionList = ProgramFunctions();
    functionList.push_back(mainFunction);
    ProgramExpression program = ProgramExpression(functionList);

    // initialize BorrowChecker
    BorrowChecker *borrowChecker = new BorrowChecker();

    // Assert
    REQUIRE_NOTHROW(program.accept(borrowChecker));

    // clean up
    delete borrowChecker;
  }

  SECTION("main Program with 1 mutable reference and 1 immutable reference "
          "assignment",
          "[assignment]") {
    /*
     *  fn main(): int {
     *    let mut x: int = 0;
     *    let a: &int = &x;
     *    let b: &int = &mut x;
     *    return 0;
     *  }
     * */
    InstructionList instructionList = InstructionList();

    // Program Instructins
    VariableAssignmentExpression *assignment = new VariableAssignmentExpression(
        new TerminalExpression(0), new VariableExpression("x"), true, "int");
    ReturnExpression *returnExpression =
        new ReturnExpression(new TerminalExpression(0));
    ReferenceAssignmentExpression *referenceA =
        new ReferenceAssignmentExpression("a", "x", "&int", false);
    ReferenceAssignmentExpression *referenceB =
        new ReferenceAssignmentExpression("b", "x", "&int", true);

    // adding them to main function declaration together with argument list
    instructionList.push_back(assignment);
    instructionList.push_back(referenceA);
    instructionList.push_back(referenceB);
    instructionList.push_back(returnExpression);
    BlockExpression *programInstructionList =
        new BlockExpression(instructionList);
    ArgumentList args = ArgumentList();
    FunctionDeclaration *mainFunction =
        new FunctionDeclaration("main", "int", programInstructionList);

    // Create Program from list of available functions i.e. AST
    ProgramFunctions functionList = ProgramFunctions();
    functionList.push_back(mainFunction);
    ProgramExpression program = ProgramExpression(functionList);

    // initialize BorrowChecker
    BorrowChecker *borrowChecker = new BorrowChecker();

    // Assert
    REQUIRE_THROWS_AS(program.accept(borrowChecker), std::invalid_argument);

    // clean up
    delete borrowChecker;
  }

  SECTION("main Program with 2 mutable reference assignment", "[assignment]") {
    /*
     *  fn main(): int {
     *    let mut x: int = 0;
     *    let a: &int = &mut x;
     *    let b: &int = &mut x;
     *    return 0;
     *  }
     * */
    InstructionList instructionList = InstructionList();

    // Program Instructins
    VariableAssignmentExpression *assignment = new VariableAssignmentExpression(
        new TerminalExpression(0), new VariableExpression("x"), true, "int");
    ReturnExpression *returnExpression =
        new ReturnExpression(new TerminalExpression(0));
    ReferenceAssignmentExpression *referenceA =
        new ReferenceAssignmentExpression("a", "x", "&int", true);
    ReferenceAssignmentExpression *referenceB =
        new ReferenceAssignmentExpression("b", "x", "&int", true);

    // adding them to main function declaration together with argument list
    instructionList.push_back(assignment);
    instructionList.push_back(referenceA);
    instructionList.push_back(referenceB);
    instructionList.push_back(returnExpression);
    BlockExpression *programInstructionList =
        new BlockExpression(instructionList);
    ArgumentList args = ArgumentList();
    FunctionDeclaration *mainFunction =
        new FunctionDeclaration("main", "int", programInstructionList);

    // Create Program from list of available functions i.e. AST
    ProgramFunctions functionList = ProgramFunctions();
    functionList.push_back(mainFunction);
    ProgramExpression program = ProgramExpression(functionList);

    // initialize BorrowChecker
    BorrowChecker *borrowChecker = new BorrowChecker();

    // Assert
    REQUIRE_THROWS_AS(program.accept(borrowChecker), std::invalid_argument);

    // clean up
    delete borrowChecker;
  }
}
