#ifndef _SERIALIZE_CODE_GEN_NAMESPACE_INTERNAL_H_
#define _SERIALIZE_CODE_GEN_NAMESPACE_INTERNAL_H_

#include <StdExt/String.h>

#include <Serialize/XML/XML.h>
#include <Serialize/XML/Element.h>

#include <memory>
#include <map>

namespace Serialize::CodeGen
{
	class NamespaceInternal final
	{
	public:
		StdExt::String FullName;
		StdExt::String Name;
		Documentation Docs;

		std::map<StdExt::String, std::shared_ptr<NamespaceInternal>> Namespaces;
		std::weak_ptr<NamespaceInternal> Parent;
	};
}

#endif // !_SERIALIZE_CODE_GEN_NAMESPACE_INTERNAL_H_
