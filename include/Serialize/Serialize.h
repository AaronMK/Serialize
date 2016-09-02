#ifndef _SERIALIZE_H_
#define _SERIALIZE_H_

#include "ByteStream.h"
#include "Types.h"

#include <cassert>
#include <string>

/**
 * Adding Support for New Datatypes
 * ------------------
 *
 * To add serialization support for new types, add specializations
 * read<T>() and write<T>() into the Serialize namespace.
 * These functions can simply utilize Bytestream::readRaw()
 * and Bytestream::writeRaw(), but they can also chain other read and write
 * specializations.  Take the following types for example:
 *
 * @code
 * struct xyCoord
 * {
 * 	int16_t x;
 * 	int16_t y;
 * };
 * 
 * struct WindowPos
 * {
 * 	xyCoord topLeft;
 * 	int16_t witdth;
 * 	int16_t height; 
 * };
 * @endcode 
 *
 * The following code would add serialization support for these types:
 *
 * @code
 * namespace Serialize
 * {
 *	template<>
 *	bool read<xyCoord>(ByteStream* stream, xyCoord *out)
 *	{
 * 		xyCoord tmpOut;
 * 		seek_t backSeek = stream->getSeekPosition();
 * 
 *		if (read<int16_t>(stream, &tmpOut.x) && read<int16_t>(stream, &tmpOut.y))
 *		{
 *			if (out)
 *				*out = tmpOut;
 *
 *			return true;
 *		}
 *
 *		stream->seek(backSeek);
 *		return false;
 *	}
 *
 *	template<>
 *	bool write<xyCoord>(ByteStream* stream, const xyCoord &val)
 *	{
 *		seek_t backSeek = stream->getSeekPosition();
 *
 *		if (write<int16_t>(stream, val.x) && write<int16_t>(stream, val.y))
 *			return true;

 *		stream->seek(backSeek);
 *		return false;
 *	}
 *
 *	template<>
 *	bool read<WindowPos>(ByteStream* stream, WindowPos *out)
 *	{
 *		WindowPos tmpOut;
 *		seek_t backSeek = stream->getSeekPosition();
 *
 *		if ( read<xyCoord>(stream, &tmpOut.topLeft) &&
 *		     read<int16_t>(stream, &tmpOut.witdth) && 
 *		     read<int16_t>(stream, &tmpOut.height))
 *		{
 *			if (out)
 *				*out = tmpOut;
 *
 *			return true;
 *		}
 *
 *		stream->seek(backSeek);
 *		return false;
 *	}
 *
 *	template<>
 *	bool write<WindowPos>(ByteStream* stream, const WindowPos &val)
 *	{
 *		seek_t backSeek = stream->getSeekPosition();
 *
 *		if ( write<xyCoord>(stream, val.topLeft) &&
 *		     write<int16_t>(stream, val.witdth) &&
 *		     write<int16_t>(stream, val.height))
 *		{
 *			return true;
 *		}
 *
 *		stream->seek(backSeek);
 *		return false;
 *	}
 *}
 * @endcode
 */
namespace Serialize
{
	/**
	 * @brief
	 *  Reads data from the passed stream and de-serializes that data into a T value
	 *  that is stored in out.  If successful true is returned and stream remains
	 *  seeked passed the data read.  If unsuccessful, false is returned, and if the stream
	 *  has seeking support, is returned to its original seek position.
	 *
	 *  If out is a nullptr, the function should read as it normally would including seeking
	 *  of the stream if the read would be successful, just not storing the value as it
	 *  normally would.
	 *
	 *  If the read is not successful, the object to which out points should remain unchanged,
	 *  but in the interest of simplifying code, this is not required.
	 *  
	 *  This function must be specialized for type support.  Otherwise, the default
	 *  implementation will be compiled and generate an error. 
	 */
	template<typename T>
	bool read(ByteStream* stream, T *out)
	{
		// Read needs to be specialized for the type.
		assert(false);

		// This function should generate a compile error of
		// not returning a value if the compiler ever tries
		// use it, which would indicate no specialization
		// being available.
	}

	/**
	 * @brief
	 *  Serializes the passed T value and writes that data to the passed stream. 
	 *  If successful true is returned and stream remains seeked passed the data
	 *  read.  If unsuccessful, false is returned. If the stream
	 *  has seeking support, is returned to its original seek position.
	 *
	 *  This function must be specialized for type support.  Otherwise, the default
	 *  implementation will be compiled and generate an error.
	 */
	template<typename T>
	bool write(ByteStream* stream, const T &val)
	{
		// Write needs to be specialized for the type.
		assert(false);

		// This function should generate a compile error of
		// not returning a value if the compiler ever tries
		// use it, which would indicate no specialization
		// being available.
	}

	template<typename T>
	bool read(ByteStream* stream, T *out, size_t count)
	{
		seek_t backSeek = stream->getSeekPosition();

		for (size_t i = 0; i < count; i++)
		{
			if (false == read<T>(stream, &out[i]))
			{
				stream->seek(backSeek);
				return false;
			}
		}

		return true;
	}

	template<typename T>
	bool write(ByteStream* stream, const T *vals, size_t count)
	{
		seek_t backSeek = stream->getSeekPosition();

		for (size_t i = 0; i < count; i++)
		{
			if (false == write<T>(stream, vals[i]))
			{
				stream->seek(backSeek);
				return false;
			}
		}

		return true;
	}

	template<>
	SERIALIZE_EXPORT bool read<uint8_t>(ByteStream* stream, uint8_t *out);

	template<>
	SERIALIZE_EXPORT bool write<uint8_t>(ByteStream* stream, const uint8_t &val);

	template<>
	SERIALIZE_EXPORT bool read<uint16_t>(ByteStream* stream, uint16_t *out);

	template<>
	SERIALIZE_EXPORT bool write<uint16_t>(ByteStream* stream, const uint16_t &val);

	template<>
	SERIALIZE_EXPORT bool read<uint32_t>(ByteStream* stream, uint32_t *out);

	template<>
	SERIALIZE_EXPORT bool write<uint32_t>(ByteStream* stream, const uint32_t &val);

	template<>
	SERIALIZE_EXPORT bool read<int8_t>(ByteStream* stream, int8_t *out);

	template<>
	SERIALIZE_EXPORT bool write<int8_t>(ByteStream* stream, const int8_t &val);

	template<>
	SERIALIZE_EXPORT bool read<int16_t>(ByteStream* stream, int16_t *out);

	template<>
	SERIALIZE_EXPORT bool write<int16_t>(ByteStream* stream, const int16_t &val);

	template<>
	SERIALIZE_EXPORT bool read<int32_t>(ByteStream* stream, int32_t *out);

	template<>
	SERIALIZE_EXPORT bool write<int32_t>(ByteStream* stream, const int32_t &val);

	template<>
	SERIALIZE_EXPORT bool read<float32_t>(ByteStream* stream, float32_t *out);

	template<>
	SERIALIZE_EXPORT bool write<float32_t>(ByteStream* stream, const float32_t &val);

	template<>
	SERIALIZE_EXPORT bool read<float64_t>(ByteStream* stream, float64_t *out);

	template<>
	SERIALIZE_EXPORT bool write<float64_t>(ByteStream* stream, const float64_t &val);

	template<>
	SERIALIZE_EXPORT bool read<std::string>(ByteStream* stream, std::string *out);

	template<>
	SERIALIZE_EXPORT bool write<std::string>(ByteStream* stream, const std::string &val);
}

#endif // _SERIALIZE_H_