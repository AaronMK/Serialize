#ifndef _SERIALIZE_TEST_BYTE_STREAM_H_
#define _SERIALIZE_TEST_BYTE_STREAM_H_

#include "ByteStream.h"

namespace Serialize
{
	/**
	 * A byte stream that does not actually write anything.  It can be used to determine
	 * seek positions after a series of operations, or as simply a black hole.  Of course,
	 * read operations will fail.
	 */
	class SERIALIZE_EXPORT TestByteStream : public ByteStream
	{
	public:
		TestByteStream();
		virtual ~TestByteStream();

		virtual bool readRaw(void* destination, bytesize_t byteLength) override;
		virtual bool writeRaw(const void* data, bytesize_t byteLength) override;
		virtual bool seek(seek_t position) override;
		virtual seek_t getSeekPosition() const override;
		virtual bytesize_t bytesAvailable() const override;
		virtual bool canRead(bytesize_t numBytes) override;
		virtual bool canWrite(bytesize_t numBytes, bool autoExpand = false) override;
		virtual bool clear() override;

	private:
		seek_t mSeekPosition;
		seek_t mMaxSeek;
	};
}

#endif // _SERIALIZE_TEST_BYTE_STREAM_H_