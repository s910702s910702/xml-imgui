#include "xml_imgui/cli.hpp"

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

  {
    const char* argv[] = {"xml_imgui_cli"};
    const auto options = xml_imgui::parse_cli(1, argv);
    failures += expect(options.ok, "empty cli options should parse");
    failures +=
        expect(options.action == xml_imgui::CliAction::ParseStdin, "default action should parse stdin");
  }

  {
    const char* argv[] = {"xml_imgui_cli", "--help"};
    const auto options = xml_imgui::parse_cli(2, argv);
    failures += expect(options.ok, "help option should parse");
    failures += expect(options.action == xml_imgui::CliAction::ShowHelp, "help action should be selected");
  }

  {
    const char* argv[] = {"xml_imgui_cli", "--version"};
    const auto options = xml_imgui::parse_cli(2, argv);
    failures += expect(options.ok, "version option should parse");
    failures +=
        expect(options.action == xml_imgui::CliAction::ShowVersion, "version action should be selected");
  }

  {
    const char* argv[] = {"xml_imgui_cli", "--wat"};
    const auto options = xml_imgui::parse_cli(2, argv);
    failures += expect(!options.ok, "unknown option should fail");
  }

  const auto usage = xml_imgui::cli_usage();
  failures += expect(!usage.empty(), "usage text should not be empty");
  failures += expect(usage.find("--help") != std::string_view::npos, "usage should include help flag");
  failures += expect(usage.find("--version") != std::string_view::npos, "usage should include version flag");

  return failures;
}
