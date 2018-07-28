#include <Serialize/CodeGen/Namespace.h>

#include <Serialize/CodeGen/Enumeration.h>
#include <Serialize/CodeGen/Exceptions.h>
#include <Serialize/CodeGen/Document.h>
#include <Serialize/CodeGen/Type.h>

#include "NamespaceInternal.h"

namespace Serialize::CodeGen
{
	Namespace::Namespace(const StdExt::String& name, Namespace* parent)
	{
		if (parent)
		{
			auto iterator = parent->mInternal->Namespaces.find(name);

			if (iterator != parent->mInternal->Namespaces.end())
			{
				mInternal = (*iterator).second;
			}
			else
			{
				mInternal = std::make_shared<NamespaceInternal>(name);
				parent->mInternal->Namespaces[mInternal->Name] = mInternal;
			}
		}
		else
		{
			mInternal = std::make_shared<NamespaceInternal>(name);
		}
	}

	Namespace::~Namespace()
	{
	}

	const StdExt::String& Namespace::name() const
	{
		return mInternal->Name;
	}

	Namespace* Namespace::addNamespace(const StdExt::String& name)
	{
		return addChildNode<Namespace>(name, this);
	}

	void Namespace::setParent(Node* parent)
	{
		if (typeid(parent) == typeid(Namespace))
		{
			Namespace* parentNS = dynamic_cast<Namespace*>(parent);

			auto iterator = parentNS->mInternal->Namespaces.find(mInternal->Name);
		}
		else if (typeid(parent) != typeid(Document))
		{
			throw InvalidParent("Namespace can only be parented by a another Namespace or a Document.");
		}

		Node::setParent(parent);
	}

	////////////////////////////////

	NamespaceInternal::NamespaceInternal(const StdExt::String& name)
		: Name(name)
	{
		parent = nullptr;
	}

	NamespaceInternal::~NamespaceInternal()
	{
		for (auto current : Namespaces)
			current.second->parent = nullptr;
	}

	NamespaceInternal::Reference NamespaceInternal::findNamespace(const StdExt::String& name)
	{
		auto iterator = Namespaces.find(name);

		if (iterator != Namespaces.end())
			return (*iterator).second;

		return Reference();
	}
}