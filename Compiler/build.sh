#!/bin/bash

setup_dependencies() {
  echo "Setting up dependencies..."
  sudo apt-get update
  sudo apt-get install -y cmake ninja-build catch2
}

build() {
  echo "Building compiler..."
  [ -d build ] || mkdir build

  cmake -GNinja -S . -B build || { echo "CMake failed"; exit 1;}

  pushd build > /dev/null
  ninja || { echo "Ninja build failed"; exit 1;}
  popd > /dev/null
}

test_compiler() {
  echo "Testing compiler..."
  pushd build > /dev/null
  ./tests || { echo "Tests failed"; exit 1;}
  popd > /dev/null
}

clean() {
  echo "Cleaning build..."
  rm -rf build
}

case "$1" in 
  setup)
    setup_dependencies
    ;;
  test)
    build
    test_compiler
    ;;
  clean)
    clean
    ;;
  *)
    build
    ;;
esac
