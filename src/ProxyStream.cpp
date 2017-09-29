#include <Serialize/ProxyStream.h>
#include <Serialize/Exceptions.h>

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
		if (nullptr == mStream)
			throw InvalidOperation("Attempting to write on an uninitialized ProxyStream.");

		if (seekPos >= mSize)
			throw OutOfBounds();

		return mStream->dataPtr(seekPos + mSeekOffset);
	}

	void ProxyStream::readRaw(void* destination, bytesize_t byteLength)
	{
		if (nullptr == mStream)
			throw InvalidOperation("Attempting to read on an uninitialized ProxyStream.");

		if ((mLocalSeek + byteLength) > mSize)
			throw OutOfBounds();

		SeekBackup seekBack(mStream);
		
		mStream->seek(mSeekOffset + mLocalSeek);
		mStream->readRaw(destination, byteLength);
		mLocalSeek += byteLength;
	}

	void ProxyStream::writeRaw(const void* data, bytesize_t byteLength)
	{
		if (nullptr == mStream)
			throw InvalidOperation("Attempting to write on an uninitialized ProxyStream.");

		if ((mLocalSeek + byteLength) > mSize)
			throw OutOfBounds();

		SeekBackup seekBack(mStream);

		mStream->seek(mSeekOffset + mLocalSeek);
		mStream->writeRaw(data, byteLength);
		mLocalSeek += byteLength;
	}

	void ProxyStream::seek(seek_t position)
	{
		if (nullptr == mStream)
			throw InvalidOperation("Attempting to seek on an uninitialized ProxyStream.");
			
		if (position >= mSize)
			throw OutOfBounds();

		mLocalSeek = position;
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

	void ProxyStream::clear()
	{
		if (nullptr == mStream)
			throw InvalidOperation("Attempting to clear on an uninitialized ProxyStream.");

		seek(0);
	}
}