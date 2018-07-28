#include <Serialize/CodeGen/Type.h>

namespace Serialize::CodeGen
{
	class TypeShared final
	{
	public:
		TypeShared();
		~TypeShared();

		TypeShared* BaseType;
	};

	////////////////////////////////

	Type::Type(const StdExt::String& name, Namespace& namesapce)
	{
	}

	Type::Type(const StdExt::String& name)
		: Node()
	{
		mShared = std::make_shared<TypeShared>();
	}

	Type::~Type()
	{
	}

	void Type::setBaseType(const Type& type)
	{
	}

	void Type::addField(const Type& type, const StdExt::String& name)
	{
	}

	//////////////////////////////////

	TypeShared::TypeShared()
	{
	}

	TypeShared::~TypeShared()
	{
	}
}