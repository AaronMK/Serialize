#include <Serialize/ByteStream.h>

#include <assert.h>

namespace Serialize
{
	ByteStream::ByteStream()
	{
		mFlags = INVALID;
	}

	ByteStream::~ByteStream()
	{

	}

	bool ByteStream::isValid() const
	{
		return ((mFlags & INVALID) == 0);
	}

	void* ByteStream::dataPtr(seek_t seekPos) const
	{
		// This will fail if the stream is marked as being
		// memory backed, but does not override dataPtr.
		assert(0 == (getFlags() & MEMORY_BACKED));

		return nullptr;
	}

	uint32_t ByteStream::getFlags() const
	{
		return mFlags;
	}

	void ByteStream::setFlags(uint32_t mask)
	{
		mFlags = mask;
	}
}