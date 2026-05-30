#include "xml_imgui/cli.hpp"

#include <CLI/CLI.hpp>

namespace xml_imgui {
namespace {

void configure_app(CLI::App& app, bool& show_version) {
  app.set_help_flag("-h,--help", "Show this help message");
  app.add_flag("-v,--version", show_version, "Show version information");
}

}  // namespace

CliOptions parse_cli(int argc, const char* const argv[]) {
  bool show_version = false;
  CLI::App app{"Reads XML from stdin and prints the parsed root node.", "xml_imgui_cli"};
  configure_app(app, show_version);

  try {
    app.parse(argc, argv);
  } catch (const CLI::CallForHelp&) {
    return {
        .action = CliAction::ShowHelp,
        .ok = true,
        .error = {},
    };
  } catch (const CLI::ParseError& error) {
    return {
        .action = CliAction::ParseStdin,
        .ok = false,
        .error = error.what(),
    };
  }

  if (show_version) {
    return {
        .action = CliAction::ShowVersion,
        .ok = true,
        .error = {},
    };
  }

  return {};
}

std::string cli_usage() {
  bool show_version = false;
  CLI::App app{"Reads XML from stdin and prints the parsed root node.", "xml_imgui_cli"};
  configure_app(app, show_version);
  return app.help();
}

}  // namespace xml_imgui
