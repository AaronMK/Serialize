#ifndef _SERIALIZE_CODE_GEN_NAMESPACE_H_
#define _SERIALIZE_CODE_GEN_NAMESPACE_H_

#include "Documentation.h"

#include <StdExt/String.h>

#include <map>
#include <memory>

namespace Serialize::CodeGen
{
	class NamespaceInternal;
	class DocumentInternal;

	class SERIALIZE_EXPORT Namespace
	{
		friend class Document;
		friend class NamespaceInternal;

	public:
		const StdExt::String& name() const;
		Namespace getNamespace(const StdExt::String& name);

		Documentation Docs;

	private:
		std::shared_ptr<NamespaceInternal> mNamespaceInternal;
		std::shared_ptr<DocumentInternal> mDocInternal;
	};
}

#endif // !_SERIALIZE_CODE_GEN_NAMESPACE_H_