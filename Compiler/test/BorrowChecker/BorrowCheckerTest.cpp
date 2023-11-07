#include "Visitors/borrowChecker.hpp"
#include "../../src/Lexer/parser.hpp"
#include "Expressions/baseExpression.hpp"
#include "Expressions/binaryExpression.hpp"
#include "Expressions/blockExpression.hpp"
#include "Expressions/functionCall.hpp"
#include "Expressions/functionDeclaration.hpp"
#include "Expressions/ifExpression.hpp"
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

extern ProgramExpression *rootAST;
extern FILE *yyin;

// The helper function to set up the environment and parse the input file
void SetUpParserAndParseFile(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Input file not found");
    throw std::runtime_error("Failed to open input file");
  }

  yyin = file;
  if (yyparse() != 0) {
    fclose(file);
    throw std::runtime_error("Parsing failed");
  }
  fclose(file);
}

// A fixture class that you can use to set up and tear down each test case
struct ParserFixture {
  ProgramExpression *rootAST;

  ParserFixture() : rootAST(nullptr) {
    // Initialize your parser here if needed
  }

  ~ParserFixture() { rootAST = nullptr; }

  void parseInput(const char *filename) {
    SetUpParserAndParseFile(filename);
    // Assume yyin and rootAST are set by the parser
    rootAST = ::rootAST;
  }
};

TEST_CASE_METHOD(ParserFixture, "BorrowCheckers", "[Assignment]") {
  SECTION("empty Main Program", "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/emptyProgram.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_NOTHROW(rootAST->accept(&borrowChecker));
  }

  SECTION("Main Program with 1 assignment", "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/assignment1.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_NOTHROW(rootAST->accept(&borrowChecker));
  }
  SECTION("main Program with 1 immutable reference assignment",
          "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/immutableReferenceAssignment.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_NOTHROW(rootAST->accept(&borrowChecker));
  }

  SECTION("main Program with 3 immutable refference assignments",
          "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/immutableReferenceAssignment3.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_NOTHROW(rootAST->accept(&borrowChecker));
  }

  SECTION("main Program with 1 mutable reference assignment",
          "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/mutableReferenceAssignment.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_NOTHROW(rootAST->accept(&borrowChecker));
  }

  SECTION("main Profram with 1 mutable reference and 1 immutable reference",
          "[BorrowChecker]") {
    parseInput(
        "test/BorrowChecker/tests/mutableAndImmutableReferenceAssignment.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_THROWS_AS(rootAST->accept(&borrowChecker), std::invalid_argument);
  }

  SECTION("main Program with 2 mutable reference assignment",
          "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/mutableReferenceAssignment2.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_THROWS_AS(rootAST->accept(&borrowChecker), std::invalid_argument);
  }

  SECTION("variable use after ownership change", "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/variableUseAfterOwnershipChange.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_THROWS_AS(rootAST->accept(&borrowChecker), std::invalid_argument);
  }

  SECTION("variable not used after ownership change", "[BorrowChecker]") {
    parseInput(
        "test/BorrowChecker/tests/variableNotUsedAfterOwnershipChange.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_NOTHROW(rootAST->accept(&borrowChecker));
  }

  SECTION("variable used after function Borrow", "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/variableUsedAfterFunctionBorrow.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_NOTHROW(rootAST->accept(&borrowChecker));
  }

  SECTION("referemce Assignment after ownership change", "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/"
               "referenceAssignmentAfterOwnershipChange.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_THROWS_AS(rootAST->accept(&borrowChecker), std::invalid_argument);
  }

  SECTION("variable used after ownership change in nested scope",
          "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/"
               "variableUsedAfterOwnershipChangeNestedScope.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_THROWS_AS(rootAST->accept(&borrowChecker), std::invalid_argument);
  }

  SECTION("variable used after ownership change of shadowed variable in nested "
          "scope",
          "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/"
               "variableUsedAfterOwnershipChangeNestedScopeShadowed.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_NOTHROW(rootAST->accept(&borrowChecker));
  }

  SECTION("variable reassigned after ownership change", "[BorrowChecker]") {
    parseInput(
        "test/BorrowChecker/tests/variableReassignedAfterOwnershipChange.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_THROWS_AS(rootAST->accept(&borrowChecker), std::invalid_argument);
  }

  SECTION("variable used after borrowing inside nested scope",
          "[BorrowChecker]") {
    parseInput(
        "test/BorrowChecker/tests/variableUsedAfterBorrowingNestedScope.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_NOTHROW(rootAST->accept(&borrowChecker));
  }

  SECTION("reference assignment to variable after ownership change of shadowed "
          "variable",
          "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/"
               "referenceAssignmentAfterOwnershipChangeShadowed.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_NOTHROW(rootAST->accept(&borrowChecker));
  }

  SECTION("function call with reference argument after ownership changed with "
          "function call",
          "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/"
               "functionCallWithReferenceArgumentAfterOwnershipChange.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_THROWS_AS(rootAST->accept(&borrowChecker), std::invalid_argument);
  }

  SECTION("function call with reference argument before ownership changed with "
          "function call",
          "[BorrowChecker]") {
    parseInput("test/BorrowChecker/tests/"
               "functionCallWithReferenceArgumentBeforeOwnershipChange.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_NOTHROW(rootAST->accept(&borrowChecker));
  }

  SECTION("function correctly transfer ownership out of a function",
          "[BorrowChecker]") {
    parseInput(
        "test/BorrowChecker/tests/functionCorrectlyTransferOwnershipOut.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_NOTHROW(rootAST->accept(&borrowChecker));
  }

  SECTION("reference becomes invalid after function call with original "
          "variable because ownership change",
          "[BorrowChecker]") {
    parseInput(
        "test/BorrowChecker/tests/"
        "referenceBecomesInvalidAfterFunctionCallWithOriginalVariable.code");

    REQUIRE(rootAST != nullptr);

    BorrowChecker borrowChecker;

    REQUIRE_THROWS_AS(rootAST->accept(&borrowChecker), std::invalid_argument);
  }
}
