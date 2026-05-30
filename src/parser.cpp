#include "xml_imgui/parser.hpp"

#include <cctype>
#include <string_view>

namespace xml_imgui {
namespace {

std::string_view trim(std::string_view value) {
  while (!value.empty() && std::isspace(static_cast<unsigned char>(value.front()))) {
    value.remove_prefix(1);
  }
  while (!value.empty() && std::isspace(static_cast<unsigned char>(value.back()))) {
    value.remove_suffix(1);
  }
  return value;
}

}  // namespace

ParseResult parse_xml(std::string_view xml) {
  const auto input = trim(xml);
  if (input.empty()) {
    return {.ok = false, .root = {}, .error = "XML input is empty"};
  }

  if (input.front() != '<') {
    return {.ok = false, .root = {}, .error = "XML input must start with '<'"};
  }

  const auto tag_end = input.find_first_of(" />");
  if (tag_end == std::string_view::npos || tag_end <= 1) {
    return {.ok = false, .root = {}, .error = "Could not read root tag"};
  }

  Node root;
  root.tag = std::string(input.substr(1, tag_end - 1));
  return {.ok = true, .root = root, .error = {}};
}

}  // namespace xml_imgui
