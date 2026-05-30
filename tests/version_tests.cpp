#include "xml_imgui/version.hpp"

#include <gtest/gtest.h>

#include <cctype>
#include <string_view>

namespace {

bool has_four_numeric_parts(std::string_view version) {
  int part_count = 1;
  bool saw_digit_in_part = false;

  for (const char character : version) {
    if (character == '.') {
      if (!saw_digit_in_part) {
        return false;
      }

      ++part_count;
      saw_digit_in_part = false;
      continue;
    }

    if (!std::isdigit(static_cast<unsigned char>(character))) {
      return false;
    }

    saw_digit_in_part = true;
  }

  return part_count == 4 && saw_digit_in_part;
}

}  // namespace

TEST(VersionTests, UsesMajorMinorPatchCommitFormat) {
  const std::string_view version = xml_imgui::version();

  EXPECT_FALSE(version.empty());
  EXPECT_TRUE(has_four_numeric_parts(version));
}
