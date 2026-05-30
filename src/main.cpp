#include "xml_imgui/cli.hpp"
#include "xml_imgui/parser.hpp"
#include "xml_imgui/version.hpp"

#include <iostream>
#include <iterator>
#include <string>

int main(int argc, const char* const argv[]) {
  const auto options = xml_imgui::parse_cli(argc, argv);
  if (!options.ok) {
    std::cerr << options.error << "\n\n" << xml_imgui::cli_usage();
    return 2;
  }

  if (options.action == xml_imgui::CliAction::ShowHelp) {
    std::cout << xml_imgui::cli_usage();
    return 0;
  }

  if (options.action == xml_imgui::CliAction::ShowVersion) {
    std::cout << "xml-imgui " << xml_imgui::version() << '\n';
    return 0;
  }

  const std::string xml(std::istreambuf_iterator<char>(std::cin), {});
  const auto result = xml_imgui::parse_xml(xml);

  if (!result.ok) {
    std::cerr << "xml-imgui " << xml_imgui::version() << ": " << result.error << '\n';
    return 1;
  }

  std::cout << "root: " << result.root.tag << '\n';
  return 0;
}
