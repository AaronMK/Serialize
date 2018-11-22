#include <Serialize/CodeGen/Document.h>

#include <Serialize/CodeGen/Enumeration.h>
#include <Serialize/CodeGen/Namespace.h>
#include <Serialize/CodeGen/Type.h>

#include <Serialize/XML/Element.h>
#include <Serialize/XML/CoreTypes.h>

#include "StringLiterals.h"

#include "NamespaceInternal.h"

using namespace std;
using namespace StdExt;

namespace Serialize::CodeGen
{
	Document::Document()
	{
	}

	Document::Document(std::string_view filePath)
		: Document()
	{
		XML::Element root = XML::Element::openFile(filePath);

		root.iterateChildren(
			[this](const XML::Element& childElement)
			{
				if (childElement.name() == slNamespace)
				{
					childElement.getAttribute<String>(slName);
				}
			}
		);
	}

	Document::~Document()
	{
	}

	Namespace Document::getNamespace(const StdExt::String& name)
	{
		auto itr = mNamespaces.find(name);
		shared_ptr<NamespaceInternal> nsInternal;

		if (itr == mNamespaces.end())
		{
			nsInternal = std::make_shared<NamespaceInternal>();
			nsInternal->Name = name;
			nsInternal->FullName = name;

			mNamespaces[name] = nsInternal;
		}
		else
		{
			nsInternal = (*itr).second;
		}

		Namespace nsReturn;
		nsReturn.mNamespaceInternal = nsInternal;
		nsReturn.mDocInternal = mDocInternal;

		return nsReturn;
	}
}