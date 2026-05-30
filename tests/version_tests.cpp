#include "xml_imgui/version.hpp"

#include <cctype>
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

int main() {
  int failures = 0;

  const std::string_view version = xml_imgui::version();
  failures += expect(!version.empty(), "version should not be empty");
  failures += expect(has_four_numeric_parts(version), "version should use major.minor.patch.commit format");

  return failures;
}
