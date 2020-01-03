#ifndef _SERIALIZE_CODEGEN_ENUMERATION_INTERNAL_H_
#define _SERIALIZE_CODEGEN_ENUMERATION_INTERNAL_H_

#include <Serialize/CodeGen/Type.h>

#include <StdExt/String>

#include <map>

namespace Serialize::CodeGen
{
	class EnumerationInternal
	{
	public:
		CoreType UnderlyingType;
		std::map<int32_t, StdExt::String> Options;
	};
}

#endif // _SERIALIZE_CODEGEN_ENUMERATION_INTERNAL_H_