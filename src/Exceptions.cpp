#include <Serialize/Exceptions.h>

namespace Serialize
{
	/////////////////////////////////

	FormatException::FormatException()
		: runtime_error("Invalid data detected during serialization.")
	{
	}

	FormatException::FormatException(const std::string& strMsg)
		: runtime_error(strMsg)
	{
	}

	FormatException::FormatException(const char* message)
		: runtime_error(message)
	{
	}

	//////////////////////////////////////

	InvalidOperation::InvalidOperation()
		: logic_error("An invalid operation was attempted.")
	{

	}

	InvalidOperation::InvalidOperation(const char* message)
		: logic_error(message)
	{
	}

	InvalidOperation::InvalidOperation(const std::string& message)
		: logic_error(message)
	{
	}

	//////////////////////////////////////

	OutOfBounds::OutOfBounds()
		: out_of_range("Reading, writing, or seeking outside the boundaries of the stream was attempted.")
	{

	}

	OutOfBounds::OutOfBounds(const char* message)
		: out_of_range(message)
	{
	}

	OutOfBounds::OutOfBounds(const std::string& message)
		: out_of_range(message)
	{
	}
}