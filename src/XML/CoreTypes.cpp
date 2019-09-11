#include <Serialize/XML/CoreTypes.h>

#include <Serialize/Exceptions.h>

#include "ElementInternal.h"

using namespace StdExt;

namespace Serialize::XML::Text
{
	template<>
	void read<bool>(const StdExt::String& string, bool* out)
	{
		if (string.compare("true") == 0)
			*out  = true;
		else if (string.compare("false") == 0)
			*out = false;
		else
			throw FormatException("Text for bool must either be 'true' or 'false'.");
	}

	template<>
	StdExt::String write<bool>(const bool &val)
	{
		return val ? StringLiteral("true") : StringLiteral("false");
	}

	template<>
	void read<uint8_t>(const StdExt::String& string, uint8_t* out)
	{
		*out = Number::parse(string).value<uint8_t>();
	}

	template<>
	StdExt::String write<uint8_t>(const uint8_t& val)
	{
		return Number(val).toString();
	}

	template<>
	void read<uint16_t>(const StdExt::String& string, uint16_t* out)
	{
		*out = Number::parse(string).value<uint16_t>();
	}

	template<>
	StdExt::String write<uint16_t>(const uint16_t& val)
	{
		return Number(val).toString();
	}

	template<>
	void read<uint32_t>(const StdExt::String& string, uint32_t* out)
	{
		*out = Number::parse(string).value<uint32_t>();
	}

	template<>
	StdExt::String write<uint32_t>(const uint32_t& val)
	{
		return Number(val).toString();
	}

	template<>
	void read<uint64_t>(const StdExt::String& string, uint64_t* out)
	{
		*out = Number::parse(string).value<uint64_t>();
	}

	template<>
	StdExt::String write<uint64_t>(const uint64_t& val)
	{
		return Number(val).toString();
	}

	template<>
	void read<int8_t>(const StdExt::String& string, int8_t* out)
	{
		*out = Number::parse(string).value<int8_t>();
	}

	template<>
	StdExt::String write<int8_t>(const int8_t& val)
	{
		return Number(val).toString();
	}

	template<>
	void read<int16_t>(const StdExt::String& string, int16_t* out)
	{
		*out = Number::parse(string).value<int16_t>();
	}

	template<>
	StdExt::String write<int16_t>(const int16_t& val)
	{
		return Number(val).toString();
	}

	template<>
	void read<int32_t>(const StdExt::String& string, int32_t* out)
	{
		*out = Number::parse(string).value<int32_t>();
	}

	template<>
	StdExt::String write<int32_t>(const int32_t& val)
	{
		return Number(val).toString();
	}

	template<>
	void read<int64_t>(const StdExt::String& string, int64_t* out)
	{
		*out = Number::parse(string).value<int64_t>();
	}

	template<>
	StdExt::String write<int64_t>(const int64_t& val)
	{
		return Number(val).toString();
	}

	template<>
	void read<StdExt::float32_t>(const StdExt::String& string, StdExt::float32_t* out)
	{
		*out = Number::parse(string).value<float32_t>();
	}

	template<>
	StdExt::String write<StdExt::float32_t>(const StdExt::float32_t& val)
	{
		return Number(val).toString();
	}

	template<>
	void read<StdExt::float64_t>(const StdExt::String& string, StdExt::float64_t* out)
	{
		*out = Number::parse(string).value<float64_t>();
	}

	template<>
	StdExt::String write<StdExt::float64_t>(const StdExt::float64_t& val)
	{
		return Number(val).toString();
	}

	template<>
	void read<std::string>(const StdExt::String& string, std::string* out)
	{
		*out = string.toStdString();
	}

	template<>
	StdExt::String write<std::string>(const std::string& val)
	{
		return StdExt::String(val);
	}

	template<>
	void read<StdExt::String>(const StdExt::String& string, StdExt::String* out)
	{
		*out = string;
	}

	template<>
	StdExt::String write<StdExt::String>(const StdExt::String& val)
	{
		return val;
	}
}

namespace Serialize::XML
{
	template<>
	void read<StdExt::String>(const Element& element, StdExt::String* out)
	{
		Text::read<StdExt::String>(element.text(), out);
	}

	template<>
	void write<StdExt::String>(Element& element, const StdExt::String& val)
	{
		element.setText(val);
	}

	template<>
	void read<std::string>(const Element& element, std::string* out)
	{
		Text::read<std::string>(element.text(), out);
	}

	template<>
	void write<std::string>(Element& element, const std::string& val)
	{
		element.setText(StdExt::String(val));
	}
}