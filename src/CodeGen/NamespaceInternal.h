#ifndef _SERIALIZE_CODE_GEN_NAMESPACE_INTERNAL_H_
#define _SERIALIZE_CODE_GEN_NAMESPACE_INTERNAL_H_

#include <StdExt/String.h>

#include <memory>
#include <map>

namespace Serialize::CodeGen
{
	class NamespaceInternal final
	{
	public:
		using Reference = std::shared_ptr<NamespaceInternal>;

		NamespaceInternal(const StdExt::String& name);
		~NamespaceInternal();

		NamespaceInternal* parent;

		StdExt::String Name;
		Documentation Docs;

		std::map<StdExt::String, Reference> Namespaces;

		Reference findNamespace(const StdExt::String& name);
	};
}

#endif // !_SERIALIZE_CODE_GEN_NAMESPACE_INTERNAL_H_
