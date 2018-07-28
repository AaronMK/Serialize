#include <Serialize/CodeGen/Enumeration.h>

namespace Serialize::CodeGen
{
	Enumeration::Enumeration(const StdExt::String& name)
		: Type(name)
	{
	}

	Enumeration::~Enumeration()
	{
	}
}