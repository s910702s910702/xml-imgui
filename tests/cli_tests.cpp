#include "xml_imgui/cli.hpp"

#include <gtest/gtest.h>

#include <string_view>

TEST(CliTests, UsesStdinParsingByDefault) {
  const char* argv[] = {"xml_imgui_cli"};

  const auto options = xml_imgui::parse_cli(1, argv);

  EXPECT_TRUE(options.ok);
  EXPECT_EQ(options.action, xml_imgui::CliAction::ParseStdin);
}

TEST(CliTests, ParsesHelpFlag) {
  const char* argv[] = {"xml_imgui_cli", "--help"};

  const auto options = xml_imgui::parse_cli(2, argv);

  EXPECT_TRUE(options.ok);
  EXPECT_EQ(options.action, xml_imgui::CliAction::ShowHelp);
}

TEST(CliTests, ParsesShortHelpFlag) {
  const char* argv[] = {"xml_imgui_cli", "-h"};

  const auto options = xml_imgui::parse_cli(2, argv);

  EXPECT_TRUE(options.ok);
  EXPECT_EQ(options.action, xml_imgui::CliAction::ShowHelp);
}

TEST(CliTests, ParsesVersionFlag) {
  const char* argv[] = {"xml_imgui_cli", "--version"};

  const auto options = xml_imgui::parse_cli(2, argv);

  EXPECT_TRUE(options.ok);
  EXPECT_EQ(options.action, xml_imgui::CliAction::ShowVersion);
}

TEST(CliTests, ParsesShortVersionFlag) {
  const char* argv[] = {"xml_imgui_cli", "-v"};

  const auto options = xml_imgui::parse_cli(2, argv);

  EXPECT_TRUE(options.ok);
  EXPECT_EQ(options.action, xml_imgui::CliAction::ShowVersion);
}

TEST(CliTests, RejectsUnknownOptions) {
  const char* argv[] = {"xml_imgui_cli", "--wat"};

  const auto options = xml_imgui::parse_cli(2, argv);

  EXPECT_FALSE(options.ok);
  EXPECT_FALSE(options.error.empty());
}

TEST(CliTests, ProvidesUsageText) {
  const auto usage = xml_imgui::cli_usage();

  EXPECT_FALSE(usage.empty());
  EXPECT_NE(usage.find("--help"), std::string_view::npos);
  EXPECT_NE(usage.find("--version"), std::string_view::npos);
}
