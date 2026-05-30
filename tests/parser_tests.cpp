#include "xml_imgui/parser.hpp"

#include <iostream>
#include <string_view>

namespace {

int expect(bool condition, std::string_view message) {
  if (!condition) {
    std::cerr << "FAIL: " << message << '\n';
    return 1;
  }
  return 0;
}

}  // namespace

int main() {
  int failures = 0;

  const auto valid = xml_imgui::parse_xml("<Window title=\"Demo\"></Window>");
  failures += expect(valid.ok, "valid XML should parse");
  failures += expect(valid.root.tag == "Window", "root tag should be Window");

  const auto empty = xml_imgui::parse_xml("   ");
  failures += expect(!empty.ok, "empty XML should fail");

  const auto invalid = xml_imgui::parse_xml("Window");
  failures += expect(!invalid.ok, "XML without opening bracket should fail");

  return failures;
}
