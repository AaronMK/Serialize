#ifndef _SERIALIZE_PROXY_STREAM_H_
#define _SERIALIZE_PROXY_STREAM_H_

#include "ByteStream.h"

namespace Serialize
{
	/**
	 * Stream interface that acts as a zero-seek based proxy to a subset of
	 * another stream.  It maintains its own interal seek, and restores the
	 * seek state of the parent stream after each operation.
	 */
	class SERIALIZE_EXPORT ProxyStream : public ByteStream
	{
	public:
		ProxyStream();
		virtual ~ProxyStream();

		bool setParams(ByteStream* stream, seek_t start);

		/**
		 * Sets the proxy to a specific position and range of the parent stream.
		 */
		bool setParams(ByteStream* stream, seek_t start, bytesize_t amt);

		virtual void* dataPtr(seek_t seekPos) const override;
		virtual bool readRaw(void* destination, bytesize_t byteLength) override;
		virtual bool writeRaw(const void* data, bytesize_t byteLength) override;
		virtual bool seek(seek_t position) override;
		virtual seek_t getSeekPosition() const override;
		virtual bytesize_t bytesAvailable() const override;
		virtual bool canRead(bytesize_t numBytes) override;
		virtual bool canWrite(bytesize_t numBytes, bool autoExpand = false) override;
		virtual bool clear() override;

	private:
		ByteStream* mStream;
		seek_t mSeekOffset;
		seek_t mLocalSeek;
		bytesize_t mSize;
	};
}

#endif // _SERIALIZE_PROXY_STREAM_H_