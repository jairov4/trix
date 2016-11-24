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

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/generated")

add_definitions(${LLVM_DEFINITIONS})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(COCO_PATH "tools/Coco-osx")
ELSEIF(WIN32)
  set(COCO_PATH "tools/Coco-win.exe")
ENDIF()

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
  "${COCO_PATH}" ARGS src/Trix.atg -namespace trix -frames src -o "${CMAKE_CURRENT_BINARY_DIR}/generated"
WORKING_DIRECTORY
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
add_executable(trix
  src/Trix.cpp
  src/SymbolTable.cpp
  "${CMAKE_CURRENT_BINARY_DIR}/generated/Parser.cpp"
  "${CMAKE_CURRENT_BINARY_DIR}/generated/Scanner.cpp"
)
target_compile_features(trix PRIVATE cxx_alias_templates)

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(trix ${llvm_libs})

install (TARGETS trix DESTINATION bin)
