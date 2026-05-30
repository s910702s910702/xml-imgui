#include "xml_imgui/parser.hpp"
#include "xml_imgui/version.hpp"

#include <iostream>
#include <iterator>
#include <string>

int main() {
  const std::string xml(std::istreambuf_iterator<char>(std::cin), {});
  const auto result = xml_imgui::parse_xml(xml);

  if (!result.ok) {
    std::cerr << "xml-imgui " << xml_imgui::version() << ": " << result.error << '\n';
    return 1;
  }

  std::cout << "root: " << result.root.tag << '\n';
  return 0;
}
