#ifndef _SERIALIZE_CODE_GEN_FIELD_H_
#define _SERIALIZE_CODE_GEN_FIELD_H_

#include "Type.h"
#include "Documentation.h"

#include <string>
#include <memory>

namespace Serialize
{
	namespace CodeGen
	{
		class TypeInternal;

		class SERIALIZE_EXPORT Field
		{
		public:
			Field(const StdExt::String& pName);
			virtual ~Field();

			StdExt::String name();
			Type* type();

			bool isMutable;
			Documentation Docs;

		private:
			StdExt::String mName;
			std::shared_ptr<TypeInternal> mType;
		};
	}
}

#endif // !_SERIALIZE_CODE_GEN_FIELD_H_