#include "xml_imgui/parser.hpp"

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <memory>
#include <string>

namespace xml_imgui {
namespace {

struct XmlDocDeleter {
  void operator()(xmlDocPtr doc) const {
    xmlFreeDoc(doc);
  }
};

struct XmlCharDeleter {
  void operator()(xmlChar* value) const {
    xmlFree(value);
  }
};

using XmlDoc = std::unique_ptr<xmlDoc, XmlDocDeleter>;
using XmlString = std::unique_ptr<xmlChar, XmlCharDeleter>;

std::string to_string(const xmlChar* value) {
  if (value == nullptr) {
    return {};
  }
  return reinterpret_cast<const char*>(value);
}

std::string content_of(xmlNodePtr node) {
  XmlString content(xmlNodeGetContent(node));
  return to_string(content.get());
}

Node convert_node(xmlNodePtr xml_node) {
  Node node;
  node.tag = to_string(xml_node->name);
  node.location.line = xmlGetLineNo(xml_node);

  for (xmlAttrPtr attr = xml_node->properties; attr != nullptr; attr = attr->next) {
    XmlString value(xmlNodeListGetString(xml_node->doc, attr->children, 1));
    node.attributes.push_back({
        .name = to_string(attr->name),
        .value = to_string(value.get()),
    });
  }

  for (xmlNodePtr child = xml_node->children; child != nullptr; child = child->next) {
    if (child->type == XML_ELEMENT_NODE) {
      node.children.push_back(convert_node(child));
    } else if (child->type == XML_TEXT_NODE || child->type == XML_CDATA_SECTION_NODE) {
      node.text += content_of(child);
    }
  }

  return node;
}

}  // namespace

ParseResult parse_xml(std::string_view xml) {
  if (xml.empty()) {
    return {.ok = false, .root = {}, .error = "XML input is empty"};
  }

  XmlDoc doc(xmlReadMemory(
      xml.data(),
      static_cast<int>(xml.size()),
      "input.xml",
      nullptr,
      XML_PARSE_NONET | XML_PARSE_NOBLANKS | XML_PARSE_NOERROR | XML_PARSE_NOWARNING));

  if (!doc) {
    return {.ok = false, .root = {}, .error = "Failed to parse XML"};
  }

  xmlNodePtr root = xmlDocGetRootElement(doc.get());
  if (root == nullptr) {
    return {.ok = false, .root = {}, .error = "XML document has no root element"};
  }

  return {.ok = true, .root = convert_node(root), .error = {}};
}

}  // namespace xml_imgui
