#include <Serialize/CachedStream.h>
#include <Serialize/Exceptions.h>

#include "private_include/Utility.h"

namespace Serialize
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
		: mDataSize(0), mData(nullptr)
	{
		if (nullptr == stream)
			throw std::invalid_argument("Parameter 'stream' cannot be null.");

		try
		{
			mData = malloc(dataSize);

			mSeekOffset = mSeekPoint = stream->getSeekPosition();
			stream->readRaw(mData, dataSize);

			mDataSize = dataSize;

			setFlags(READ_ONLY | MEMORY_BACKED);
		}
		catch (std::exception &ex)
		{
			clear();
			throw ex;
		}
	}

	CachedStream::CachedStream(ByteStream* stream, seek_t beginSeek, bytesize_t dataSize)
		: mDataSize(0), mData(nullptr)
	{
		setCachedData(stream, beginSeek, dataSize);
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

	void CachedStream::setCachedData(ByteStream* stream, seek_t beginSeek, bytesize_t dataSize)
	{
		if (0 == (stream->getFlags() | CAN_SEEK))
			throw InvalidOperation("Source stream must be able to seek for non-advancing CachedStream input.");

		if (nullptr == stream)
			throw std::invalid_argument("Parameter 'stream' cannot be null.");

		try
		{
			clear();

			SeekBackup seekBack(stream);

			mData = malloc(dataSize);

			mSeekOffset = mSeekPoint = beginSeek;
			stream->readRaw(mData, dataSize);

			mDataSize = dataSize;

			setFlags(READ_ONLY | MEMORY_BACKED);
		}
		catch (std::exception &ex)
		{
			clear();
			throw ex;
		}
	}

	void CachedStream::readRaw(void* destination, bytesize_t byteLength)
	{
		if ((byteLength + mSeekPoint) > (mSeekOffset + mDataSize))
			throw OutOfBounds("Attempted to read outside of the stream.");

		if (destination)
			memcpy(destination, &((char*)mData)[mSeekPoint - mSeekOffset], byteLength);

		mSeekPoint += byteLength;
	}

	void CachedStream::seek(seek_t position)
	{
		if (position >= mSeekOffset && position < (mSeekOffset + mDataSize))
			mSeekPoint = position;
		else
			throw OutOfBounds("Attempted to seek outside of the stream.");
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

	void CachedStream::clear()
	{
		free(mData);
		setFlags(INVALID);

		mSeekOffset = 0;
		mSeekPoint = 0;
		bytesize_t mDataSize = 0;
		mData = nullptr;
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