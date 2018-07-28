#ifndef _SERIALIZE_CODE_GEN_DOCUMENTATION_H_
#define _SERIALIZE_CODE_GEN_DOCUMENTATION_H_

#include "../Config.h"

#include <StdExt/String.h>

namespace Serialize
{
	namespace CodeGen
	{
		struct Documentation
		{
			Documentation(Documentation&&) = default;
			Documentation& operator=(Documentation&& mE) = default;

			Documentation()
			{
			}

			bool Internal;
			StdExt::String Brief;
			StdExt::String Detailed;
		};
	}
}

#endif // !_SERIALIZE_CODE_GEN_DOCUMENTATION_H_