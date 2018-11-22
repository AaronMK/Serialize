#ifndef _SERIALIZE_BUFFERED_STREAM_H_
#define _SERIALIZE_BUFFERED_STREAM_H_

#include "ByteStream.h"

#include <StdExt/Buffer.h>

namespace Serialize::Binary
{
	class SERIALIZE_EXPORT BufferedStream : public ByteStream
	{
	public:
		BufferedStream();
		virtual ~BufferedStream();

		virtual void* dataPtr(seek_t seekPos) const override;
		virtual void readRaw(void* destination, bytesize_t byteLength) override;
		virtual void writeRaw(const void* data, bytesize_t byteLength) override;
		virtual void seek(seek_t position) override;
		virtual seek_t getSeekPosition() const override;
		virtual bytesize_t bytesAvailable() const override;
		virtual bool canRead(bytesize_t numBytes) override;
		virtual bool canWrite(bytesize_t numBytes, bool autoExpand = false) override;
		virtual void clear() override;

	private:
		StdExt::Buffer mBuffer;
		seek_t mBytesWritten;
		seek_t mSeekPosition;
	};
}

#endif // !_SERIALIZE_BUFFERED_STREAM_H_
