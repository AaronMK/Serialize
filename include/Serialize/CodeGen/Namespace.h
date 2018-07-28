#ifndef _SERIALIZE_CODE_GEN_NAMESPACE_H_
#define _SERIALIZE_CODE_GEN_NAMESPACE_H_

#include "Node.h"
#include "Documentation.h"

#include <StdExt/String.h>

#include <map>
#include <memory>

namespace Serialize::CodeGen
{
	class NamespaceInternal;
	
	class Enumeration;
	class Type;

	class SERIALIZE_EXPORT Namespace : public Node
	{
	public:
		Namespace(const Namespace&) = default;
		Namespace& operator=(const Namespace&) = default;

		Namespace(const StdExt::String& name, Namespace* parent = nullptr);

		virtual ~Namespace();

		const StdExt::String& name() const;
		Namespace* addNamespace(const StdExt::String& name);

		Documentation Docs;

	protected:
		virtual void setParent(Node* parent) override;

	private:
		std::shared_ptr<NamespaceInternal> mInternal;
	};
}

#endif // !_SERIALIZE_CODE_GEN_NAMESPACE_H_