#ifndef _RESOURCE_CACHED_STREAM_H_
#define _RESOURCE_CACHED_STREAM_H_

#include "ByteStream.h"

namespace Serialize
{
	/**
	 * Reads part of a stream into memory, presumably from a stream reading from disk, in
	 * a single read operation, and provides a ByteStream interface to that subset of the
	 * stream.  Seek points are in relation to the parent stream. Attempting to seek or
	 * read outside what is cached will fail.
	 *
	 * Once created, cached streams are not dependent on the original stream.
	 */
	class SERIALIZE_EXPORT CachedStream : public ByteStream
	{
		CachedStream& operator=(const CachedStream&) = delete;

	public:
		/**
		 * @brief
		 *  Creates an empty stream.  Only useful for situations where a default constructor is needed
		 *  and a real data will be set later.
		 */
		CachedStream();

		/**
		 * @brief
		 *  Move contructor
		 */
		CachedStream(CachedStream&& other);

		/**
		 * @brief
		 *  Creates a cached stream using the current seek position of the, and reading dataSize into
		 *  memory.  This will advance the passed stream.
		 */
		CachedStream(ByteStream* stream, bytesize_t dataSize);

		/**
		 * @brief
		 *  Creates a cached stream by copying dataSize bytes at beginSeek in stream.  No advancement
		 *  of the passed stream will take place.
		 */
		CachedStream(ByteStream* stream, seek_t beginSeek, bytesize_t dataSize);

		virtual ~CachedStream();

		virtual void* dataPtr(seek_t seekPos) const override;

		/**
		 * @brief
		 *  Sets up the cached data in the same way as the corresponding constructor.  Any existing
		 *  cached data will be freed.
		 */
		void setCachedData(ByteStream* stream, seek_t beginSeek, bytesize_t dataSize);

		virtual void readRaw(void* destination, bytesize_t byteLength) override;
		virtual void seek(seek_t position) override;
		virtual seek_t getSeekPosition() const override;
		virtual bytesize_t bytesAvailable() const override;
		virtual bool canRead(bytesize_t numBytes) override;
		virtual bool canWrite(bytesize_t numBytes, bool autoExpand = false) override;

		virtual void clear() override;

		CachedStream& operator=(CachedStream&& other);

	private:
		seek_t mSeekOffset;
		seek_t mSeekPoint;
		bytesize_t mDataSize;
		void* mData;
	};
}

#endif // _RESOURCE_CACHED_STREAM_H_