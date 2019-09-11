#ifndef _SERIALIZE_XML_H_
#define _SERIALIZE_XML_H_

#include <StdExt/String.h>

namespace Serialize::XML
{
	class Element;

	namespace Text
	{
		template<typename T>
		void read(const StdExt::String& string, T* out)
		{
			static_assert(false, "Serialize::XML::Text::read<T> needs to be specialized for the type T template parameter.");
		}

		template<typename T>
		StdExt::String write(const T& val)
		{
			static_assert(false, "Serialize::XML::Text::write<T> needs to be specialized for the type T template parameter.");
		}

		template<typename T>
		T read(const StdExt::String& string)
		{
			T ret;
			read<T>(string, &ret);

			return ret;
		}
	}

	//////////////////////////////////////////////////////

	template<typename T>
	void read(const Element& element, T* out)
	{
		if constexpr (std::is_arithmetic_v<T>)
			Text::read<T>(element.text(), out);
		else
			static_assert(false, "Serialize::XML::read<T> needs to be specialized for the type T template parameter.");
	}
	
	template<typename T>
	void write(Element& element, const T& val)
	{
		if constexpr (std::is_arithmetic_v<T>)
			element.setText(Text::write<T>());
		else
			static_assert(false, "Serialize::XML::write<T> needs to be specialized for the type T template parameter.");
	}

	template<typename T>
	T read(const Element& element)
	{
		T ret;
		read<T>(element, &ret);

		return ret;
	}
}

#endif // _SERIALIZE_XML_H_