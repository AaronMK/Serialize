#ifndef _SERIALIZE_EXCEPTIONS_H_
#define _SERIALIZE_EXCEPTIONS_H_

#include "Config.h"

#include <stdexcept>

namespace Serialize
{
	class FormatException : public std::runtime_error
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

	class InvalidOperation : public std::logic_error
	{
	public:
		InvalidOperation();
		InvalidOperation(const char* message);
		InvalidOperation(const std::string& message);
	};

	///////////////////////////////////

	class OutOfBounds : public std::out_of_range
	{
	public:
		OutOfBounds();
		OutOfBounds(const char* message);
		OutOfBounds(const std::string& message);
	};

	/////////////////////////////////

	inline FormatException::FormatException()
		: runtime_error("Invalid data detected during serialization.")
	{
	}

	inline FormatException::FormatException(const std::string& strMsg)
		: runtime_error(strMsg)
	{
	}

	inline FormatException::FormatException(const char* message)
		: runtime_error(message)
	{
	}

	//////////////////////////////////////

	inline InvalidOperation::InvalidOperation()
		: logic_error("An invalid operation was attempted.")
	{

	}

	inline InvalidOperation::InvalidOperation(const char* message)
		: logic_error(message)
	{
	}

	inline InvalidOperation::InvalidOperation(const std::string& message)
		: logic_error(message)
	{
	}

	//////////////////////////////////////

	inline OutOfBounds::OutOfBounds()
		: out_of_range("Reading, writing, or seeking outside the boundaries of the stream was attempted.")
	{

	}

	inline OutOfBounds::OutOfBounds(const char* message)
		: out_of_range(message)
	{
	}

	inline OutOfBounds::OutOfBounds(const std::string& message)
		: out_of_range(message)
	{
	}
}

#endif // _SERIALIZE_EXCEPTIONS_H_
