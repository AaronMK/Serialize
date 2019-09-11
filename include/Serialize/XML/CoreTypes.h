#ifndef _SERIALIZE_XML_CORE_TYPES_H_
#define _SERIALIZE_XML_CORE_TYPES_H_

#include "../Config.h"
#include "Element.h"

#include <StdExt/String.h>
#include <StdExt/Number.h>

#include <map>
#include <list>
#include <vector>

namespace Serialize::XML
{
	namespace Text
	{
		template<>
		SERIALIZE_EXPORT void read<bool>(const StdExt::String& string, bool* out);

		template<>
		SERIALIZE_EXPORT StdExt::String write<bool>(const bool& val);

		template<>
		SERIALIZE_EXPORT void read<uint8_t>(const StdExt::String& string, uint8_t* out);

		template<>
		SERIALIZE_EXPORT StdExt::String write<uint8_t>(const uint8_t& val);

		template<>
		SERIALIZE_EXPORT void read<uint16_t>(const StdExt::String& string, uint16_t* out);

		template<>
		SERIALIZE_EXPORT StdExt::String write<uint16_t>(const uint16_t& val);

		template<>
		SERIALIZE_EXPORT void read<uint32_t>(const StdExt::String& string, uint32_t* out);

		template<>
		SERIALIZE_EXPORT StdExt::String write<uint32_t>(const uint32_t& val);

		template<>
		SERIALIZE_EXPORT void read<uint64_t>(const StdExt::String& string, uint64_t* out);

		template<>
		SERIALIZE_EXPORT StdExt::String write<uint64_t>(const uint64_t& val);

		template<>
		SERIALIZE_EXPORT void read<int8_t>(const StdExt::String& string, int8_t* out);

		template<>
		SERIALIZE_EXPORT StdExt::String write<int8_t>(const int8_t& val);

		template<>
		SERIALIZE_EXPORT void read<int16_t>(const StdExt::String& string, int16_t* out);

		template<>
		SERIALIZE_EXPORT StdExt::String write<int16_t>(const int16_t& val);

		template<>
		SERIALIZE_EXPORT void read<int32_t>(const StdExt::String& string, int32_t* out);

		template<>
		SERIALIZE_EXPORT StdExt::String write<int32_t>(const int32_t& val);

		template<>
		SERIALIZE_EXPORT void read<int64_t>(const StdExt::String& string, int64_t* out);

		template<>
		SERIALIZE_EXPORT StdExt::String write<int64_t>(const int64_t& val);

		template<>
		SERIALIZE_EXPORT void read<StdExt::float32_t>(const StdExt::String& string, StdExt::float32_t* out);

		template<>
		SERIALIZE_EXPORT StdExt::String write<StdExt::float32_t>(const StdExt::float32_t& val);

		template<>
		SERIALIZE_EXPORT void read<StdExt::float64_t>(const StdExt::String& string, StdExt::float64_t* out);

		template<>
		SERIALIZE_EXPORT StdExt::String write<StdExt::float64_t>(const StdExt::float64_t& val);

		template<>
		SERIALIZE_EXPORT void read<std::string>(const StdExt::String& string, std::string* out);

		template<>
		SERIALIZE_EXPORT StdExt::String write<std::string>(const std::string& val);

		template<>
		SERIALIZE_EXPORT void read<StdExt::String>(const StdExt::String& string, StdExt::String* out);

		template<>
		SERIALIZE_EXPORT StdExt::String write<StdExt::String>(const StdExt::String& val);
	}

	template<>
	SERIALIZE_EXPORT void read<StdExt::String>(const Element& element, StdExt::String* out);

	template<>
	SERIALIZE_EXPORT void write<StdExt::String>(Element& element, const StdExt::String& val);

	template<>
	SERIALIZE_EXPORT void read<std::string>(const Element& element, std::string* out);

	template<>
	SERIALIZE_EXPORT void write<std::string>(Element& element, const std::string& val);

	template<typename key_t, typename value_t>
	std::map<key_t, value_t> readMap(const Element& element)
	{
		std::map<key_t, value_t> ret;

		String KeyElementName = StdExt::StringLiteral("Key");
		String ValueElementName = StdExt::StringLiteral("Value");

		element.iterateChildren(
			[&](const Element& itemElm)
			{
				key_t key;
				value_t value;

				itemElm.iterateChildren(
					[&](const Element& childElm)
					{
						StdExt::String childName = childElm.name();

						if (KeyElementName == childName)
							key = read<key_t>(childElm);
						else if (ValueElementName == childName)
							value = read<value_t>(childElm);
					}
				);

				ret[std::move(key)] = std::move(value);
			}
		);

		return ret;
	}

	template<typename key_t, typename value_t>
	void writeMap(Element& element, const std::map<key_t, value_t>& map)
	{
		if (map.size() == 0)
			return;

		String ItemElementName = StdExt::StringLiteral("Item");
		String KeyElementName = StdExt::StringLiteral("Key");
		String ValueElementName = StdExt::StringLiteral("Value");

		std::map<key_t, value_t>::const_iterator itr;

		for (itr = map.begin(); itr != map.end(); ++itr)
		{
			Element elmItem = element.addChildElement(ItemElementName);
			elmItem.addChild(KeyElementName, itr->first);
			elmItem.addChild(ValueElementName, itr->second);
		}
	}

	template<typename T>
	std::vector<T> readVector(const Element& element)
	{
		std::vector<T> ret;
		uint32_t count;

		if (element.getAttribute("Count", count) && count > 0)
			ret.reserve(count);

		element.iterateChildren(
			[&](const Element& childElm)
			{
				ret.push_back(read<T>(childElm));
			}
		);

		return ret;
	}

	template<typename T>
	void writeVector(Element& element, const std::vector<T>& val)
	{
		String ItemElementName = StdExt::StringLiteral("Item");

		element.setAttribute<uint32_t>("Count", Number(val.size()).value<uint32_t>());

		for (const T& item : val)
			element.addChild(ItemElementName, item);
	}

	template<typename T>
	std::list<T> readList(const Element& element)
	{
		std::list<T> ret;
		uint32_t count;

		element.iterateChildren(
			[&](const Element& childElm)
			{
				ret.push_back(read<T>(childElm));
			}
		);

		return ret;
	}
}

#endif // _SERIALIZE_XML_CORE_TYPES_H_