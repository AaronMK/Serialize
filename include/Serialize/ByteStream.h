#ifndef _SERIALIZE_BYTE_STREAM_H_
#define _SERIALIZE_BYTE_STREAM_H_

#include "Config.h"
#include "Types.h"

#include <type_traits>
#include <string>
#include <limits>

namespace Serialize
{
	/**
	 * Base class for all data streams. 
	 */
	class SERIALIZE_EXPORT ByteStream
	{
	public:

		/**
		 * @brief
		 *  Flags that are used to set and/or determine properties of a ByteStream.
		 */
		enum Flags : uint32_t
		{
			/**
			 * @brief
			 *  Stream is read only.
			 */
			NO_FLAGS = 0,

			/**
			 * @brief
			 *  Stream is read only.
			 */
			READ_ONLY = 1,

			/**
			 * @brief
			 *  Stream is write only.
			 */
			WRITE_ONLY = 2,

			/**
			 * @brief
			 *  Stream supports seeking.  Usually streams that do not support seeking
			 *  are sockets.
			 */
			CAN_SEEK = 4,

			/**
			 * @brief
			 *  Backing stream data is in memory, and can be accessed directly using pointers
			 *  returned by dataPtr().
			 */
			MEMORY_BACKED = 8,

			/**
			 * @brief
			 *  Indicates that the stream is not valid.
			 */
			INVALID = 16
		};

		ByteStream();
		virtual ~ByteStream();

		/**
		 * @brief
		 *  Shortcut to checking validity of the stream based on set flags.
		 */
		bool isValid() const;

		/**
		 * @brief
		 *  Gets a pointer to raw data at a seek position in the stream.  This does not
		 *  actually seek the stream, and will only work if the data backing the stream
		 *  is in memory.
		 */
		virtual void* dataPtr(seek_t seekPos) const;

		/**
		 * @brief
		 *  Reads a block of raw data from the current seek position of the file.
		 *  The seek position is moved by the number of bytes read.  If data is nullptr,
		 *  the seek position is simply moved forward by byteLength.
		 */
		virtual bool readRaw(void* destination, bytesize_t byteLength) = 0;

		/**
		 * @brief
		 *  Writes raw data to the file. The seek position is moved
		 *  by the number of bytes written.
		 */
		virtual bool writeRaw(const void* data, bytesize_t byteLength) = 0;

		/**
		 * @brief
		 *  Seeks to the position in terms of number of bytes from the beginning.
		 */
		virtual bool seek(seek_t position) = 0;

		/*
		 * @brief
		 *  Gets the current seek position on which read and write operations will take place.
		 */
		virtual seek_t getSeekPosition() const = 0;

		/**
		 * @brief
		 *  Gets the number of bytes available for reading from the current seek position.
		 */
		virtual bytesize_t bytesAvailable() const = 0;

		/**
		 * @brief
		 *  Determines if there is the specified amount of data left to read.
		 */
		virtual bool canRead(bytesize_t numBytes) = 0;

		/**
		 * @brief
		 *  Determines if the stream is capable of handling a write of the requested
		 *  size at the current seek position.  If autoExpand is true, the ByteStream
		 *  will attempt to expand to make it capable of handling the requested write
		 *  and return true if successful.
		 */
		virtual bool canWrite(bytesize_t numBytes, bool autoExpand = false) = 0;
		
		/**
		 * @brief
		 *  For writable streams, clears all contents and resets the seek position to 0.
		 */
		virtual bool clear() = 0;

		/*
		 * @brief
		 *  Gets the flags for common properties of ByteStreams.
		 */
		uint32_t getFlags() const;

	protected:
		void setFlags(uint32_t mask);

	private:
		uint32_t mFlags;
	};
}

#endif // _SERIALIZE_BYTE_STREAM_H_