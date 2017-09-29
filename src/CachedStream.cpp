#include <Resource/CachedStream.h>

namespace Resource
{
	CachedStream::CachedStream()
		: ByteStream()
	{
		setFlags(INVALID);

		mSeekOffset = 0;
		mSeekPoint = 0;
		bytesize_t mDataSize = 0;
		mData = nullptr;
	}

	CachedStream::CachedStream(CachedStream&& other)
	{
		bytesize_t mDataSize = other.mDataSize;
		other.mDataSize = 0;

		mData = other.mData;
		other.mData = nullptr;

		mSeekOffset = other.mSeekOffset;
		other.mSeekOffset = 0;

		mSeekPoint = other.mSeekPoint;
		other.mSeekPoint = 0;

		setFlags(other.getFlags());
		other.setFlags(INVALID);
	}

	CachedStream::CachedStream(ByteStream* stream, bytesize_t dataSize)
	{

	}

	CachedStream::CachedStream(ByteStream* stream, seek_t beginSeek, bytesize_t dataSize)
		: mDataSize(0), mData(nullptr)
	{
		
		if (nullptr == stream)
		{
			free(mData);
			mData = nullptr;

			mSeekOffset = mSeekPoint = 0;
			mDataSize = 0;

			setFlags(INVALID);
			return true;
		}
		
		SeekBackup seekBack(stream);

		if (false == stream->seek(beginSeek + dataSize) || false == stream->seek(beginSeek))
		{
			setFlags(INVALID);
			return false;
		}

		free(mData);
		mData = malloc(dataSize);

		mSeekOffset = mSeekPoint = beginSeek;
		stream->readRaw(mData, dataSize);

		mDataSize = dataSize;

		setFlags(READ_ONLY | MEMORY_BACKED);
	}

	CachedStream::~CachedStream()
	{
		free(mData);
	}

	void* CachedStream::dataPtr(seek_t seekPos) const
	{	
		if ( nullptr == mData || seekPos < mSeekOffset || seekPos >= (mDataSize + mSeekOffset))
			return nullptr;

		return &((char*)mData)[seekPos - mSeekOffset];
	}

	bool CachedStream::readRaw(void* destination, bytesize_t byteLength)
	{
		if ((byteLength + mSeekPoint) > (mSeekOffset + mDataSize))
			return false;

		if (destination)
			memcpy(destination, &((char*)mData)[mSeekPoint - mSeekOffset], byteLength);

		mSeekPoint += byteLength;
		return true;
	}

	bool CachedStream::writeRaw(const void* data, bytesize_t byteLength)
	{
		return false;
	}

	bool CachedStream::seek(seek_t position)
	{
		if (position >= mSeekOffset && position < (mSeekOffset + mDataSize))
		{
			mSeekPoint = position;
			return true;
		}

		return false;
	}

	seek_t CachedStream::getSeekPosition() const
	{
		return mSeekPoint;
	}

	bytesize_t CachedStream::bytesAvailable() const
	{
		bytesize_t ret = mDataSize - (mSeekPoint - mSeekOffset);
		return ret;
	}


	bool CachedStream::canRead(bytesize_t numBytes)
	{
		return ((numBytes + mSeekPoint) < (mDataSize + mSeekOffset));
	}

	bool CachedStream::canWrite(bytesize_t numBytes, bool autoExpand)
	{
		return false;
	}

	bool CachedStream::clear()
	{
		return false;
	}

	CachedStream& CachedStream::operator=(CachedStream&& other)
	{
		bytesize_t mDataSize = other.mDataSize;
		other.mDataSize = 0;

		mData = other.mData;
		other.mData = nullptr;

		mSeekOffset = other.mSeekOffset;
		other.mSeekOffset = 0;

		mSeekPoint = other.mSeekPoint;
		other.mSeekPoint = 0;

		setFlags(other.getFlags());
		other.setFlags(INVALID);

		return *this;
	}
}