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
  failures += expect(valid.root.attributes.size() == 1, "root should have one attribute");
  failures += expect(valid.root.attributes[0].name == "title", "attribute name should parse");
  failures += expect(valid.root.attributes[0].value == "Demo", "attribute value should parse");

  const auto nested =
      xml_imgui::parse_xml("<Window><Text value=\"Hello\"/><Button id=\"ok\">OK</Button></Window>");
  failures += expect(nested.ok, "nested XML should parse");
  failures += expect(nested.root.children.size() == 2, "root should have two children");
  failures += expect(nested.root.children[0].tag == "Text", "first child should be Text");
  failures += expect(nested.root.children[1].tag == "Button", "second child should be Button");
  failures += expect(nested.root.children[1].text == "OK", "text content should parse");

  const auto empty = xml_imgui::parse_xml("   ");
  failures += expect(!empty.ok, "empty XML should fail");

  const auto invalid = xml_imgui::parse_xml("Window");
  failures += expect(!invalid.ok, "XML without opening bracket should fail");

  return failures;
}
