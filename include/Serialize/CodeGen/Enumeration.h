#ifndef _SERIALIZE_CODE_GEN_ENUMERATION_H_
#define _SERIALIZE_CODE_GEN_ENUMERATION_H_

#include "Type.h"
#include "Documentation.h"

#include <StdExt/Number.h>

#include <list>
#include <optional>

namespace Serialize::CodeGen
{
	class SERIALIZE_EXPORT Enumeration : public Type
	{
	public:
		struct Option
		{
			Documentation Docs;
			std::string Name;
		};

		Enumeration(const StdExt::String& name);
		virtual ~Enumeration();

		Documentation Docs;
		std::list<Option> Options;
	};
}

#endif // !_SERIALIZE_CODE_GEN_ENUMERATION_H_