#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace xml_imgui {

struct Attribute {
  std::string name;
  std::string value;
};

struct Node {
  std::string tag;
  std::vector<Attribute> attributes;
  std::vector<Node> children;
};

struct ParseResult {
  bool ok;
  Node root;
  std::string error;
};

ParseResult parse_xml(std::string_view xml);

}  // namespace xml_imgui
