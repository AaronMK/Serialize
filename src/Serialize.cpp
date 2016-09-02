#include <Serialize/Serialize.h>
#include <Serialize/ByteStream.h>

namespace Serialize
{
	template<>
	bool read<uint8_t>(ByteStream* stream, uint8_t *out)
	{
		return stream->readRaw(out, sizeof(uint8_t));
	}

	template<>
	bool write<uint8_t>(ByteStream* stream, const uint8_t &val)
	{
		return stream->writeRaw(&val, sizeof(uint8_t));
	}

	template<>
	bool read<uint16_t>(ByteStream* stream, uint16_t *out)
	{
		return stream->readRaw(out, sizeof(uint16_t));
	}

	template<>
	bool write<uint16_t>(ByteStream* stream, const uint16_t &val)
	{
		return stream->writeRaw(&val, sizeof(uint16_t));
	}

	template<>
	bool read<uint32_t>(ByteStream* stream, uint32_t *out)
	{
		return stream->readRaw(out, sizeof(uint32_t));
	}

	template<>
	bool write<uint32_t>(ByteStream* stream, const uint32_t &val)
	{
		return stream->writeRaw(&val, sizeof(uint32_t));
	}


	template<>
	bool read<int8_t>(ByteStream* stream, int8_t *out)
	{
		return stream->readRaw(out, sizeof(int8_t));
	}

	template<>
	bool write<int8_t>(ByteStream* stream, const int8_t &val)
	{
		return stream->writeRaw(&val, sizeof(int8_t));
	}

	template<>
	bool read<int16_t>(ByteStream* stream, int16_t *out)
	{
		return stream->readRaw(out, sizeof(int16_t));
	}

	template<>
	bool write<int16_t>(ByteStream* stream, const int16_t &val)
	{
		return stream->writeRaw(&val, sizeof(int16_t));
	}

	template<>
	bool read<int32_t>(ByteStream* stream, int32_t *out)
	{
		return stream->readRaw(out, sizeof(int32_t));
	}

	template<>
	bool write<int32_t>(ByteStream* stream, const int32_t &val)
	{
		return stream->writeRaw(&val, sizeof(int32_t));
	}

	template<>
	bool read<float32_t>(ByteStream* stream, float32_t *out)
	{
		return stream->readRaw(out, sizeof(float32_t));
	}

	template<>
	bool write<float32_t>(ByteStream* stream, const float32_t &val)
	{
		return stream->writeRaw(&val, sizeof(float32_t));
	}

	template<>
	bool read<float64_t>(ByteStream* stream, float64_t *out)
	{
		return stream->readRaw(out, sizeof(float64_t));
	}

	template<>
	bool write<float64_t>(ByteStream* stream, const float64_t &val)
	{
		return stream->writeRaw(&val, sizeof(float64_t));
	}

	template<>
	bool read<std::string>(ByteStream* stream, std::string *out)
	{
		seek_t back = stream->getSeekPosition();

		uint32_t length;
		if (read<uint32_t>(stream, &length))
		{
			if (out)
			{
				std::string str;
				str.resize(length);

				if (stream->readRaw((void*)str.data(), length))
				{
					*out = std::move(str);
					return true;
				}
			}
			else
			{
				return stream->readRaw(nullptr, length);
			}
		}

		stream->seek(back);
		return false;
	}

	template<>
	bool write<std::string>(ByteStream* stream, const std::string &val)
	{
		seek_t back = stream->getSeekPosition();
		uint32_t length = static_cast<uint32_t>(val.length());

		if (write(stream, length) && stream->writeRaw(val.data(), length))
			return true;

		stream->seek(back);
		return false;
	}
}