cmake_minimum_required(VERSION 3.20)

project(
  xml_imgui
  VERSION 0.1.0
  DESCRIPTION "Convert declarative XML UI descriptions into Dear ImGui C++ object trees"
  LANGUAGES CXX
)

option(XML_IMGUI_BUILD_TESTS "Build xml_imgui tests" ON)
option(XML_IMGUI_BUILD_EXAMPLES "Build xml_imgui examples" ON)

find_package(LibXml2 REQUIRED)
find_package(CLI11 REQUIRED)
find_package(Git QUIET)

set(XML_IMGUI_VERSION_BASE "${PROJECT_VERSION}")
set(XML_IMGUI_COMMIT_COUNT "0")

if(Git_FOUND)
  execute_process(
    COMMAND "${GIT_EXECUTABLE}" describe --tags --abbrev=0
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    OUTPUT_VARIABLE XML_IMGUI_GIT_TAG
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  execute_process(
    COMMAND "${GIT_EXECUTABLE}" rev-list --count HEAD
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    OUTPUT_VARIABLE XML_IMGUI_GIT_COMMIT_COUNT
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  if(XML_IMGUI_GIT_TAG)
    string(REGEX REPLACE "^v" "" XML_IMGUI_VERSION_BASE "${XML_IMGUI_GIT_TAG}")
  endif()

  if(XML_IMGUI_GIT_COMMIT_COUNT)
    set(XML_IMGUI_COMMIT_COUNT "${XML_IMGUI_GIT_COMMIT_COUNT}")
  endif()
endif()

set(XML_IMGUI_VERSION_STRING "${XML_IMGUI_VERSION_BASE}.${XML_IMGUI_COMMIT_COUNT}")

configure_file(
  cmake/version_config.hpp.in
  "${PROJECT_BINARY_DIR}/generated/xml_imgui/version_config.hpp"
  @ONLY
)

add_library(xml_imgui
  src/cli.cpp
  src/parser.cpp
  src/version.cpp
)

add_library(xml_imgui::xml_imgui ALIAS xml_imgui)

target_include_directories(xml_imgui
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/generated>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(xml_imgui PUBLIC cxx_std_20)

target_link_libraries(xml_imgui PUBLIC CLI11::CLI11 LibXml2::LibXml2)

if(MSVC)
  target_compile_options(xml_imgui PRIVATE /W4 /permissive-)
else()
  target_compile_options(xml_imgui PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(XML_IMGUI_BUILD_EXAMPLES)
  add_executable(xml_imgui_cli src/main.cpp)
  target_link_libraries(xml_imgui_cli PRIVATE xml_imgui::xml_imgui)
endif()

if(XML_IMGUI_BUILD_TESTS)
  enable_testing()
  include(GoogleTest)
  find_package(GTest REQUIRED)

  function(xml_imgui_add_unit_test target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} PRIVATE GTest::gtest_main xml_imgui::xml_imgui)
    gtest_discover_tests(${target})
  endfunction()

  xml_imgui_add_unit_test(xml_imgui_cli_tests tests/cli_tests.cpp)
  xml_imgui_add_unit_test(xml_imgui_parser_tests tests/parser_tests.cpp)
  xml_imgui_add_unit_test(xml_imgui_version_tests tests/version_tests.cpp)
endif()
