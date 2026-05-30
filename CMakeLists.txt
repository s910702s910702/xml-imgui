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

add_library(xml_imgui
  src/parser.cpp
  src/version.cpp
)

add_library(xml_imgui::xml_imgui ALIAS xml_imgui)

target_include_directories(xml_imgui
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(xml_imgui PUBLIC cxx_std_20)

target_link_libraries(xml_imgui PUBLIC LibXml2::LibXml2)

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
  add_executable(xml_imgui_tests tests/parser_tests.cpp)
  target_link_libraries(xml_imgui_tests PRIVATE xml_imgui::xml_imgui)
  add_test(NAME xml_imgui_tests COMMAND xml_imgui_tests)
endif()
