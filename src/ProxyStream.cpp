#include <Serialize/ProxyStream.h>

#include <algorithm>

namespace Serialize
{
	
	/**
	 * @internal
	 *
	 * @brief
	 *  Autmatically stores the seek position of a stream and seeks
	 *  the stream back to that position upon destruction.
	 */
	class SeekBackup
	{
		ByteStream* mStream;
		seek_t mBackSeek;
	public:
		SeekBackup(ByteStream* stream)
		{
			mStream = stream;
			mBackSeek = mStream->getSeekPosition();
		}

		~SeekBackup()
		{
			mStream->seek(mBackSeek);
		}
	};

	///////////////////////////////

	ProxyStream::ProxyStream()
		: ByteStream()
	{
		mStream = nullptr;
		mSeekOffset = 0;
		mLocalSeek = 0;
		mSize = 0;

		setFlags(INVALID);
	}

	ProxyStream::~ProxyStream()
	{

	}

	bool ProxyStream::setParams(ByteStream* stream, seek_t start)
	{
		bytesize_t amt = std::numeric_limits<bytesize_t>::max();
		return setParams(stream, start, amt);
	}

	bool ProxyStream::setParams(ByteStream* stream, seek_t start, bytesize_t amt)
	{
		mStream = stream;
		
		if (stream == nullptr)
		{
			mSeekOffset = 0;
			mLocalSeek = 0;
			mSize = 0;

			setFlags(INVALID);

			return true;
		}

		setFlags(stream->getFlags());

		mStream = stream;
		mSeekOffset = start;
		mLocalSeek = 0;
		mSize = amt;

		return true;
	}

	void* ProxyStream::dataPtr(seek_t seekPos) const
	{
		if (nullptr == mStream || seekPos >= mSize)
			return nullptr;

		return mStream->dataPtr(seekPos + mSeekOffset);
	}

	bool ProxyStream::readRaw(void* destination, bytesize_t byteLength)
	{
		if (nullptr == mStream || (mLocalSeek + byteLength) > mSize)
			return false;

		SeekBackup seekBack(mStream);
		mStream->seek(mSeekOffset + mLocalSeek);

		if (mStream->readRaw(destination, byteLength))
		{
			mLocalSeek += byteLength;
			return true;
		}

		return false;
	}

	bool ProxyStream::writeRaw(const void* data, bytesize_t byteLength)
	{
		if (nullptr == mStream || (mLocalSeek + byteLength) > mSize)
			return false;

		SeekBackup seekBack(mStream);
		mStream->seek(mSeekOffset + mLocalSeek);

		if (mStream->writeRaw(data, byteLength))
		{
			mLocalSeek += byteLength;
			return true;
		}

		return false;
	}

	bool ProxyStream::seek(seek_t position)
	{
		if (nullptr == mStream || position >= mSize)
			return false;

		mLocalSeek = position;
		return true;
	}

	seek_t ProxyStream::getSeekPosition() const
	{
		return mLocalSeek;
	}

	bytesize_t ProxyStream::bytesAvailable() const
	{
		static const bytesize_t maxSize = std::numeric_limits<bytesize_t>::max();
		
		if (nullptr == mStream)
			return 0;
		
		SeekBackup seekBack(mStream);

		mStream->seek(mSeekOffset + mLocalSeek);

		bytesize_t streamAvail = mStream->bytesAvailable();
		bytesize_t boundedAvail = (mSize != maxSize) ? mSize - mLocalSeek : maxSize;

		return std::min(streamAvail, boundedAvail);
	}

	bool ProxyStream::canRead(bytesize_t numBytes)
	{
		if (nullptr == mStream || numBytes + mLocalSeek > mSize)
			return false;

		SeekBackup seekBack(mStream);
		mStream->seek(mSeekOffset + mLocalSeek);

		return mStream->canRead(numBytes);
	}

	bool ProxyStream::canWrite(bytesize_t numBytes, bool autoExpand)
	{
		if (nullptr == mStream || numBytes + mLocalSeek > mSize)
			return false;

		SeekBackup seekBack(mStream);
		mStream->seek(mSeekOffset + mLocalSeek);

		return mStream->canWrite(numBytes, autoExpand);
	}

	bool ProxyStream::clear()
	{
		if (nullptr == mStream)
			return false;

		return seek(0);
	}
}