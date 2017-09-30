#include <Serialize/ByteStream.h>

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
}