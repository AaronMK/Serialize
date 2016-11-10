#include <Serialize/MemoryStream.h>

namespace Serialize
{
	MemoryStream::MemoryStream()
		: ByteStream()
	{
		setFlags(READ_ONLY | MEMORY_BACKED | CAN_SEEK);

		mData = nullptr;
		mSize = 0;
		mSeekPosition = 0;
	}

	MemoryStream::MemoryStream(const void* beginning, bytesize_t size)
	{
		setFlags(MEMORY_BACKED | CAN_SEEK);

		mData = const_cast<void*>(beginning);
		mSize = (nullptr != mData) ? size : 0;
		mSeekPosition = 0;
	}

	MemoryStream::~MemoryStream()
	{
	}

	void* MemoryStream::dataPtr(seek_t seekPos) const
	{
		if (nullptr == mData || seekPos >= mSize)
			return nullptr;

		return (char*)mData + seekPos;
	}

	bool MemoryStream::readRaw(void* destination, bytesize_t byteLength)
	{
		if (nullptr == mData)
			return false;
		
		if ((mSeekPosition + byteLength) <= mSize)
		{
			if (destination)
				memcpy(destination, &((char*)mData)[mSeekPosition], byteLength);
			
			mSeekPosition += byteLength;
			return true;
		}

		return false;
	}

	bool MemoryStream::writeRaw(const void* data, bytesize_t byteLength)
	{
		if (nullptr == mData)
			return false;

		if ((getFlags() & READ_ONLY) == 0 && (mSeekPosition + byteLength) <= mSize)
		{
			memcpy(&((char*)mData)[mSeekPosition], data, byteLength);
			mSeekPosition += byteLength;
			return true;
		}

		return false;
	}

	bool MemoryStream::seek(seek_t position)
	{
		if (nullptr == mData)
			return false;

		if (position < mSize)
		{
			mSeekPosition = position;
			return true;
		}

		return false;
	}
	
	seek_t MemoryStream::getSeekPosition() const
	{
		return mSeekPosition;
	}

	bytesize_t MemoryStream::bytesAvailable() const
	{
		bytesize_t ret = mSize - mSeekPosition;
		return ret;
	}

	bool MemoryStream::canRead(bytesize_t numBytes)
	{
		if (nullptr == mData)
			return false;
		
		return ((mSeekPosition + numBytes) <= mSize);
	}

	bool MemoryStream::canWrite(bytesize_t numBytes, bool autoExpand)
	{
		if (nullptr == mData)
			return false;

		return ((getFlags() | READ_ONLY) == 0) ? ((mSeekPosition + numBytes) <= mSize) : false;
	}

	bool MemoryStream::clear()
	{
		if (nullptr == mData)
			return false;

		if ((getFlags() | READ_ONLY) == 0)
		{
			seek(0);
			return true;
		}

		return false;
	}
}