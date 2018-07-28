#ifndef _SERIALLIZE_CODE_GEN_DOCUMENT_PARSER_H_
#define _SERIALLIZE_CODE_GEN_DOCUMENT_PARSER_H_

#include <Serialize/CodeGen/Document.h>
#include <Serialize/CodeGen/Enumeration.h>
#include <Serialize/CodeGen/Documentation.h>

#include <tinyxml2.h>

#include <stack>

namespace Serialize::CodeGen
{
	class Namespace;

	class DocumentParser final
	{
	public:
		static void parse(std::string_view filePath, Document* docOut);

	private:
		DocumentParser(std::string_view, Document* docOut);
		~DocumentParser();

		void parseSerializeElement(tinyxml2::XMLElement* xmlElement);
		void parseCppElement(tinyxml2::XMLElement* element);
		void parseNamespaceElement(tinyxml2::XMLElement* xmlElement);
		void parseTypeElement(tinyxml2::XMLElement* xmlElement);
		void parseFieldElement(tinyxml2::XMLElement* xmlElement);
		void parseEnumerationElement(tinyxml2::XMLElement* xmlElement);
		Enumeration::Option parseEnumOption(tinyxml2::XMLElement* xmlElement);
		void parseDocumentationElement(tinyxml2::XMLElement* xmlElement, Documentation& out);

		Document* mDocOut;

		std::stack<Namespace*> mNamspaceStack;
		std::stack<Node*> mNodeStack;
	};
}

#endif // !_SERIALLIZE_CODE_GEN_DOCUMENT_PARSER_H_