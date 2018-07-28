#include <Serialize/CodeGen/Document.h>

#include "DocumentParser.h"

#include <Serialize/CodeGen/Enumeration.h>
#include <Serialize/CodeGen/Namespace.h>
#include <Serialize/CodeGen/Type.h>

using namespace tinyxml2;

namespace Serialize::CodeGen
{
	Document::Document()
		: Root(StdExt::String::Literal(""))
	{
	}

	Document::Document(std::string_view filePath)
		: Document()
	{
		DocumentParser::parse(filePath, this);
	}

	Document::~Document()
	{
	}

	Enumeration* Document::addEnumeration(const StdExt::String& name)
	{
		return nullptr;
	}

	Namespace* Document::addNamespace(const StdExt::String& name)
	{
		return nullptr;
	}

	Type* Document::addType(const StdExt::String& name)
	{
		return nullptr;
	}
}