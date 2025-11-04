cmake_minimum_required(VERSION 3.31)
project(iterator_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
add_compile_options(-Wall -Wextra)

add_executable(pointer-stepping
    src/pointer-stepping.cxx)

add_executable(single-linked-list
    src/containers/single-linked-list.hxx
    src/containers/ostream-iterator.hxx
    src/iterator-tests/single-linked-list.test.cxx
)
target_include_directories(single-linked-list PRIVATE src/containers)

add_executable(ostream-iterator
    src/containers/ostream-iterator.hxx
    src/iterator-tests/ostream-iterator.test.cxx)
target_include_directories(ostream-iterator PRIVATE src/containers)

add_executable(istream-iterator
    src/containers/istream-iterator.hxx
    src/iterator-tests/istream-iterator.test.cxx)
target_include_directories(istream-iterator PRIVATE src/containers)

add_executable(double-linked-list
    src/containers/double-linked-list.hxx
    src/iterator-tests/double-linked-list.test.cxx)
target_include_directories(double-linked-list PRIVATE src/containers)

add_executable(simple-vector
    src/containers/simple-vector.hxx
    src/iterator-tests/simple-vector.test.cxx)
target_include_directories(simple-vector PRIVATE src/containers)

add_executable(stl.test
    src/containers/istream-iterator.hxx
    src/containers/ostream-iterator.hxx
    src/containers/single-linked-list.hxx
    src/containers/double-linked-list.hxx
    src/containers/simple-vector.hxx
    src/stl.test.cxx)
target_include_directories(stl.test PRIVATE src/containers)


