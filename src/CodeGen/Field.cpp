#include <Serialize/CodeGen/Field.h>

namespace Serialize
{
	namespace CodeGen
	{
		Field::Field(const StdExt::String& pName)
			: mName(pName)
		{
			isMutable = false;
		}

		Field::~Field()
		{

		}

		StdExt::String Field::name()
		{
			return mName;
		}

		Type Field::type()
		{
			// TODO: insert return statement here
		}
	}
}