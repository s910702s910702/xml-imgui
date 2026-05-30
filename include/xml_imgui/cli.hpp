#pragma once

#include <string>

namespace xml_imgui {

enum class CliAction {
  ParseStdin,
  ShowHelp,
  ShowVersion,
};

struct CliOptions {
  CliAction action = CliAction::ParseStdin;
  bool ok = true;
  std::string error;
};

CliOptions parse_cli(int argc, const char* const argv[]);
std::string cli_usage();

}  // namespace xml_imgui
