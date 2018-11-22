#ifndef _SERIALIZE_CODE_GEN_DOCUMENTATION_H_
#define _SERIALIZE_CODE_GEN_DOCUMENTATION_H_

#include "../Config.h"

#include <StdExt/String.h>

#include <Serialize/Binary/Binary.h>
#include <Serialize/XML/XML.h>

namespace Serialize
{
	namespace CodeGen
	{
		struct Documentation
		{
			bool Internal;
			StdExt::String Brief;
			StdExt::String Detailed;

			bool isEmpty() const
			{
				return ((Brief.length() + Detailed.length()) == 0);
			}
		};
	}

	namespace Binary
	{
		template<>
		SERIALIZE_EXPORT void read(ByteStream* stream, CodeGen::Documentation* out);

		template<>
		SERIALIZE_EXPORT void write(ByteStream* stream, const CodeGen::Documentation& val);
	}

	namespace XML
	{
		template<>
		SERIALIZE_EXPORT void read(const Element& element, CodeGen::Documentation* out);

		template<>
		SERIALIZE_EXPORT void write(Element& element, const CodeGen::Documentation& val);
	}
}

#endif // !_SERIALIZE_CODE_GEN_DOCUMENTATION_H_