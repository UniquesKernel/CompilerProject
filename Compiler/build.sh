#!/bin/bash
execute() {
  local cmd_to_run="$1"
  local errmsg="$2"
  eval "$cmd_to_run" || { echo "Error: ${errmsg:-Execution failed}"; exit 1; }
}

setup_dependencies() {
  echo "Setting up dependencies..."
  execute "sudo apt-get update" "Failed to update apt-get"
  execute "sudo apt-get install -y cmake ninja-build catch2 lcov gcc g++ bc llvm-dev" "Failed to install dependencies"
  echo "Dependencies set up"
}

build_project() {
  echo "Building project..."
  local build_type="${1:-Debug}"
  [ -d build ] || execute "mkdir -p build" "Failed to create build directory"
  
  echo "Generating compile_commands.json..."
  echo "Generating ninja build files..."
  execute "cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=${build_type} -GNinja -S . -B build" "Failed to configure project"
  execute "cp build/compile_commands.json ." "Failed to copy compile_commands.json"

  execute "pushd build > /dev/null" ""
  echo "Compiling project with ninja..."
  execute "ninja" "Failed to build project"
  execute "popd > /dev/null" ""


  echo "Project built completed"
}

test_project() {
  echo "Testing project..."
  execute "./build/tests" "Failed to run tests"
  echo "Project tested"
}

test_project_with_coverage() {
  echo "Testing project with coverage..."

  test_project

  echo "Generating coverage report..."
  execute "lcov --capture --directory . --output-file coverage.info" "Failed to generate coverage report"
  execute "lcov --remove coverage.info '*/usr/*' '*/tests/*' --output-file coverage.filtered.info" "Failed to generate coverage report"
  echo "Coverage report generated"

  echo "Evaluate coverage report..."
  local line_coverage=$(lcov --summary coverage.filtered.info | grep lines | awk '{print $2}' | sed 's/%//')
  local is_coverage_good=$(echo "${line_coverage} < 80" | bc)
  if [ "$is_coverage_good" -eq 0 ]; then
    echo "Coverage is ${line_coverage}%"
  else
    echo "Coverage is ${line_coverage}%, which is less than 100%"
    exit 1
  fi
  echo "Coverage report evaluated"

  execute "genhtml coverage.filtered.info --output-directory coverage" "Failed to generate coverage report"
  echo "Project test completed"
}

check_format() {
  echo "Checking format..."
  for file in $(find . \( -iname '*.cpp' -o -iname '*.hpp' \) -not -path './build/*'); do
    fileDiff=$(clang-format -style=llvm $file | diff -u $file -)

    if [ ! -z "$fileDiff" ]; then
      echo "File ${file} is not formatted correctly at:"
      echo "$fileDiff"
      exit 1
    fi
  done
  echo "Format checked"
}

format_code() {
  echo "Formating..."
  for file in $(find . \( -iname '*.cpp' -o -iname '*.hpp' \) -not -path './build/*'); do
    clang-format -style=llvm -i $file
  done
  echo "Format complet"
}

clean_project() {
  echo "Cleaning project..."
  execute "rm -rf build" "Failed to remove build directory"
  execute "rm -rf compile_commands.json" "Failed to remove compile_commands.json"
  echo "Project cleaned"
}

print_help() {
  echo "Usage: ./build.sh [command]"
  echo "Commands:"
  echo "  setup             - Install dependencies."
  echo "  test              - Build and run tests."
  echo "  test_with_coverage - Run tests and generate coverage."
  echo "  clean             - Clean the project."
  echo "  help              - Print this help message."
}

case "$1" in 
  setup)
    setup_dependencies
    ;;
  test)
    build_project
    test_project
    ;;
  test_with_coverage)
    build_project "Coverage"
    test_project_with_coverage
    ;;
  check_format)
    check_format
    ;;
  format)
    format_code
    ;;
  clean)
    clean_project
    ;;
  help)
    print_help
    ;;
  *)
    build_project
    ;;
esac
