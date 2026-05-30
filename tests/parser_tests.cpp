#include "xml_imgui/parser.hpp"

#include <gtest/gtest.h>

TEST(ParserTests, ParsesRootElementAndAttributes) {
  const auto result = xml_imgui::parse_xml("<Window title=\"Demo\"></Window>");

  ASSERT_TRUE(result.ok) << result.error;
  EXPECT_EQ(result.root.tag, "Window");
  ASSERT_EQ(result.root.attributes.size(), 1U);
  EXPECT_EQ(result.root.attributes[0].name, "title");
  EXPECT_EQ(result.root.attributes[0].value, "Demo");
}

TEST(ParserTests, ParsesNestedElementsAndText) {
  const auto result =
      xml_imgui::parse_xml("<Window><Text value=\"Hello\"/><Button id=\"ok\">OK</Button></Window>");

  ASSERT_TRUE(result.ok) << result.error;
  ASSERT_EQ(result.root.children.size(), 2U);
  EXPECT_EQ(result.root.children[0].tag, "Text");
  EXPECT_EQ(result.root.children[1].tag, "Button");
  EXPECT_EQ(result.root.children[1].text, "OK");
}

TEST(ParserTests, RejectsEmptyInput) {
  const auto result = xml_imgui::parse_xml("   ");

  EXPECT_FALSE(result.ok);
}

TEST(ParserTests, RejectsInputWithoutRootElement) {
  const auto result = xml_imgui::parse_xml("Window");

  EXPECT_FALSE(result.ok);
}
