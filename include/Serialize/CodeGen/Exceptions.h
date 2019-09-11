#ifndef _SERIALIZE_CODE_GEN_EXCEPTIONS_H_
#define _SERIALIZE_CODE_GEN_EXCEPTIONS_H_

#include "../Config.h"

#include <stdexcept>

namespace Serialize::CodeGen
{
	class ParseException : public std::runtime_error
	{
	public:
		const int Line;

		ParseException(const char* message, int line);
		ParseException(const std::string& message, int line);
	};


	class InvalidParent : public std::runtime_error
	{
	public:
		InvalidParent(const char* message);
		InvalidParent(const std::string& message);
	};

	////////////////////////////////

	inline ParseException::ParseException(const char* message, int line)
		: runtime_error(message), Line(line)
	{
	}

	inline ParseException::ParseException(const std::string& message, int line)
		: runtime_error(message), Line(line)
	{
	}

	////////////////////////////////

	inline InvalidParent::InvalidParent(const char* message)
		: runtime_error(message)
	{
	}

	inline InvalidParent::InvalidParent(const std::string& message)
		: runtime_error(message)
	{
	}
}

#endif // !_SERIALIZE_CODE_GEN_EXCEPTIONS_H_