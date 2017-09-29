#include <Serialize/ByteStream.h>
#include <Serialize/Exceptions.h>

#include <assert.h>


using namespace std;

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
		throw InvalidOperation("Stream does support direct addressing of data.");
	}

	void ByteStream::readRaw(void * destination, bytesize_t byteLength)
	{
		throw InvalidOperation("Stream does not support reading.");
	}

	void ByteStream::writeRaw(const void * data, bytesize_t byteLength)
	{
		throw InvalidOperation("Stream does not support writing.");
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