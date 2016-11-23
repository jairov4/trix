PROJECT(trix)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(
  include
  "${CMAKE_CURRENT_BINARY_DIR}/generated"
  "${LLVM_INCLUDE_DIRS}"
)

add_definitions(${LLVM_DEFINITIONS})

add_custom_command(
OUTPUT
  "${CMAKE_CURRENT_BINARY_DIR}/generated/Parser.cpp"
  "${CMAKE_CURRENT_BINARY_DIR}/generated/Scanner.cpp"
  "${CMAKE_CURRENT_BINARY_DIR}/generated/Parser.h"
  "${CMAKE_CURRENT_BINARY_DIR}/generated/Scanner.h"
MAIN_DEPENDENCY
  src/Trix.atg
DEPENDS
  src/Parser.frame
  src/Scanner.frame
COMMAND
  tools/coco.exe ARGS src/Trix.atg -namespace trix -frames src -o "${CMAKE_CURRENT_BINARY_DIR}/generated"
WORKING_DIRECTORY
  "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_executable(trix
  src/Trix.cpp
  src/SymbolTable.cpp
  "${CMAKE_CURRENT_BINARY_DIR}/generated/Parser.cpp"
  "${CMAKE_CURRENT_BINARY_DIR}/generated/Scanner.cpp"
)

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(trix ${llvm_libs})

install (TARGETS trix DESTINATION bin)
