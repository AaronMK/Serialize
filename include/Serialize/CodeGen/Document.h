#ifndef _SERIALIZE_CODE_GEN_DOCUMENT_H_
#define _SERIALIZE_CODE_GEN_DOCUMENT_H_

#include "Node.h"
#include "Namespace.h"
#include "Exceptions.h"

#include <StdExt/InPlace.h>
#include <StdExt/String.h>

#include <string>
#include <memory>

namespace Serialize::CodeGen
{
	class Type;
	class Enumeration;

	class SERIALIZE_EXPORT Document : public Node
	{
		friend class DocumentParser;

		struct CppProps
		{
			StdExt::String IncludeGuard;
			StdExt::String ExportPreProcessDefine;
		};

	public:
		Document(const Document&) = delete;
		Document& operator=(const Document&) = delete;

		Document(Document&&) = default;
		Document& operator=(Document&&) = default;

		Document();
		Document(std::string_view filePath);

		~Document();

		Enumeration* addEnumeration(const StdExt::String& name);
		Namespace* addNamespace(const StdExt::String& name);
		Type* addType(const StdExt::String& name);

		CppProps CPP;

	private:
		Namespace Root;
	};
}
#endif // !_SERIALIZE_CODE_GEN_DOCUMENT_H_