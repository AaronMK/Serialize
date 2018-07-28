#include "DocumentParser.h"

#include <Serialize/CodeGen/Namespace.h>
#include <Serialize/CodeGen/Field.h>

#include <sstream>

using namespace tinyxml2;
using namespace std;

namespace Serialize::CodeGen
{
	std::string getElementText(XMLElement* element)
	{
		if (element->FirstChildElement() != nullptr)
		{
			std::stringstream ss;
			ss << "<" << element->Name() << "> must be a text-only element.";

			throw ParseException(ss.str(), element->GetLineNum());
		}

		const char* text = element->GetText();

		if (text)
			return std::string(text);
		else
			return std::string("");
	}

	void DocumentParser::parse(std::string_view filePath, Document* docOut)
	{
		DocumentParser(filePath, docOut);
	}

	DocumentParser::DocumentParser(std::string_view filePath, Document* docOut)
		: mDocOut(docOut)
	{
		mNodeStack.push(docOut);
		mNamspaceStack.push(&docOut->Root);

		XMLDocument xmlDoc;
		xmlDoc.LoadFile(filePath.data());

		XMLElement* rootElement = xmlDoc.FirstChildElement("Serialize");

		if (nullptr == rootElement)
			throw ParseException("File does not containe a <Serialize> element.", 1);

		parseSerializeElement(rootElement);
	}

	DocumentParser::~DocumentParser()
	{

	}

	void DocumentParser::parseSerializeElement(XMLElement* xmlElement)
	{
		bool nonHeaderParsed = false;

		XMLElement* elm = xmlElement->FirstChildElement();
		while (nullptr != elm)
		{
			if (strcmp("CPP", elm->Name()) == 0)
			{
				if (nonHeaderParsed)
					throw ParseException("<CPP> must come before any <NameSpace>, <Type>, or <Enumeration> elements.", elm->GetLineNum());

				parseCppElement(elm);
			}
			else if (strcmp("Namespace", elm->Name()) == 0)
			{
				parseNamespaceElement(elm);
				nonHeaderParsed = true;
			}
			else if (strcmp("Enumeration", elm->Name()) == 0)
			{
				parseEnumerationElement(elm);
			}
			else if (strcmp("Type", elm->Name()) == 0)
			{
				parseTypeElement(elm);
			}

			elm = elm->NextSiblingElement();
		};
	}

	void DocumentParser::parseCppElement(XMLElement* element)
	{
		XMLElement* IncludeGuard = element->FirstChildElement("IncludeGuard");
		if (IncludeGuard)
		{
			mDocOut->CPP.IncludeGuard = getElementText(IncludeGuard);
		}

		XMLElement* ExportPreProcessDefine = element->FirstChildElement("ExportPreProcessDefine");
		if (ExportPreProcessDefine)
			mDocOut->CPP.ExportPreProcessDefine = getElementText(ExportPreProcessDefine);
	}

	void DocumentParser::parseNamespaceElement(XMLElement* xmlElement)
	{
		const char* name = xmlElement->Attribute("name", nullptr);

		if (nullptr == name)
			throw ParseException("<Namespace> must contain a 'name' attribute.", xmlElement->GetLineNum());

		Namespace* nsNode = mNodeStack.top()->addChildNode<Namespace>(name);
		mNamspaceStack.push(nsNode);
		mNodeStack.push(nsNode);

		XMLElement* elm = xmlElement->FirstChildElement();
		while (nullptr != elm)
		{
			if (strcmp("Namespace", elm->Name()) == 0)
			{
				parseNamespaceElement(elm);
			}
			else if (strcmp("Enumeration", elm->Name()) == 0)
			{
				parseEnumerationElement(elm);
			}
			else if (strcmp("Type", elm->Name()) == 0)
			{
				parseTypeElement(elm);
			}
			else if (strcmp("Documentation", elm->Name()) == 0)
			{
				parseDocumentationElement(elm, nsNode->Docs);
			}

			elm = elm->NextSiblingElement();
		}

		mNodeStack.pop();
		mNamspaceStack.pop();
	}

	void DocumentParser::parseTypeElement(XMLElement* xmlElement)
	{
		const char* name = xmlElement->Attribute("name", nullptr);

		if (nullptr == name)
			throw ParseException("<Namespace> must contain a 'name' attribute.", xmlElement->GetLineNum());
		
		const char* base = xmlElement->Attribute("base", nullptr);

		Type* typeNode = mNodeStack.top()->addChildNode<Type>(name);
		mNodeStack.push(typeNode);

		XMLElement* elm = xmlElement->FirstChildElement();
		while (nullptr != elm)
		{
			if (strcmp("Field", elm->Name()) == 0)
			{
				parseFieldElement(elm);
			}
			else if (strcmp("Documentation", elm->Name()) == 0)
			{
				parseDocumentationElement(elm, typeNode->Docs);
			}

			elm = elm->NextSiblingElement();
		}

		mNodeStack.pop();
	}

	void DocumentParser::parseFieldElement(XMLElement* xmlElement)
	{
		const char* name = xmlElement->Attribute("name", nullptr);

		if (nullptr == name)
			throw ParseException("<Field> must contain a 'name' attribute.", xmlElement->GetLineNum());

		const char* type = xmlElement->Attribute("type", nullptr);

		if (nullptr == type)
			throw ParseException("<Field> must contain a 'type' attribute.", xmlElement->GetLineNum());

		Field* fieldNode = mNodeStack.top()->addChildNode<Field>(name);
		mNodeStack.push(fieldNode);

		XMLElement* elm = xmlElement->FirstChildElement();
		while (nullptr != elm)
		{
			if (strcmp("Documentation", elm->Name()) == 0)
			{
				parseDocumentationElement(elm, fieldNode->Docs);
			}

			elm = elm->NextSiblingElement();
		}

		fieldNode->isMutable = xmlElement->BoolAttribute("mutable");

		mNodeStack.pop();
	}


	void DocumentParser::parseEnumerationElement(tinyxml2::XMLElement* xmlElement)
	{
		const char* name = xmlElement->Attribute("name", nullptr);

		if (nullptr == name)
			throw ParseException("<Enumeration> must contain a 'name' attribute.", xmlElement->GetLineNum());

		Enumeration* enumNode = mNamspaceStack.top()->addChildNode<Enumeration>(name);
		mNodeStack.push(enumNode);

		XMLElement* elm = xmlElement->FirstChildElement();
		while (nullptr != elm)
		{
			if (strcmp("Documentation", elm->Name()) == 0)
			{
				parseDocumentationElement(elm, enumNode->Docs);
			}
			else if (strcmp("Option", elm->Name()) == 0)
			{
				const char* optionName = xmlElement->Attribute("name", nullptr);

				if (nullptr == name)
					throw ParseException("<Option> must contain a 'name' attribute.", xmlElement->GetLineNum());

				enumNode->Options.emplace_back(parseEnumOption(elm));
			}

			elm = elm->NextSiblingElement();
		}

		mNodeStack.pop();
	}

	Enumeration::Option DocumentParser::parseEnumOption(tinyxml2::XMLElement* xmlElement)
	{
		Enumeration::Option option;

		const char* name = xmlElement->Attribute("name", nullptr);

		if (nullptr == name)
			throw ParseException("<Option> must contain a 'name' attribute.", xmlElement->GetLineNum());
		else
			option.Name = name;

		XMLElement* elm = xmlElement->FirstChildElement();
		while (nullptr != elm)
		{
			if (strcmp("Documentation", elm->Name()) == 0)
				parseDocumentationElement(elm, option.Docs);

			elm = elm->NextSiblingElement();
		}

		return option;
	}

	void DocumentParser::parseDocumentationElement(XMLElement* xmlElement, Documentation& out)
	{
		out.Internal = xmlElement->BoolAttribute("internal", false);

		XMLElement* elm = xmlElement->FirstChildElement();
		while (nullptr != elm)
		{
			if (strcmp("Brief", elm->Name()) == 0)
			{
				out.Brief = getElementText(elm);
			}
			else if (strcmp("Details", elm->Name()) == 0)
			{
				out.Brief = getElementText(elm);
			}

			elm = elm->NextSiblingElement();
		}
	}
}