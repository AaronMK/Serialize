#ifndef _SERIALIZE_EXCEPTIONS_H_
#define _SERIALIZE_EXCEPTIONS_H_

#include "Config.h"

#include <stdexcept>

namespace Serialize
{
	class SERIALIZE_EXPORT FormatException : public std::runtime_error
	{
	public:
		template<typename T>
		static FormatException ForType()
		{
			return FormatException(std::string("Invalid data when reading " + typeid(T).name() + "."));
		}

		FormatException();
		FormatException(const char* message);
		FormatException(const std::string& strMsg);
	};

	///////////////////////////////////

	class SERIALIZE_EXPORT InvalidOperation : public std::logic_error
	{
	public:
		InvalidOperation();
		InvalidOperation(const char* message);
		InvalidOperation(const std::string& message);
	};

	///////////////////////////////////

	class SERIALIZE_EXPORT OutOfBounds : public std::out_of_range
	{
	public:
		OutOfBounds();
		OutOfBounds(const char* message);
		OutOfBounds(const std::string& message);
	};
}

#endif // _SERIALIZE_EXCEPTIONS_H_
