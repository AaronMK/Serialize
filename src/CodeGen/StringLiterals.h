#ifndef _SERIALIZE_XML_STRING_LITERALS_H_
#define _SERIALIZE_XML_STRING_LITERALS_H_

#include <StdExt/String.h>

namespace Serialize::CodeGen
{
	constexpr StdExt::StringLiteral slNamespace("Namespace");
	constexpr StdExt::StringLiteral slName("Name");
	constexpr StdExt::StringLiteral slField("Field");
	constexpr StdExt::StringLiteral slType("Type");
}

#endif // _SERIALIZE_XML_STRING_LITERALS_H_