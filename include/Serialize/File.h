#ifndef _SERIALIZE_FILE_H_
#define _SERIALIZE_FILE_H_

#include "ByteStream.h"

#include <stdio.h>

namespace Serialize
{
	/**
	 * File based ByteStream.
	 *
	 * An attempt to create files opened for writing is always made if they don't exist, and
	 * any file open for writing will also be readable.
	 */
	class SERIALIZE_EXPORT File : public ByteStream
	{
	public:
		File(const File&) = delete;
		File& operator=(const File&) = delete;

		File();

		/**
		 * @param path
		 *    Either an absolute or relative path to the file.
		 *
		 * @param readonly
		 *    Designates whether the file will only be opened for reading. 
		 */
		File(const char* path, bool readonly);

		/**
		 * Move constructor.  The entire state of other, including seek position
		 * and status, will be moved to the new object.
		 */
		File(File &&other);
		
		virtual ~File();

		virtual bool readRaw(void* destination, bytesize_t byteLength) override;
		virtual bool writeRaw(const void* data, bytesize_t byteLength) override;
		virtual bool seek(seek_t position) override;
		virtual seek_t getSeekPosition() const override;
		virtual bytesize_t bytesAvailable() const override;
		virtual bool canRead(bytesize_t numBytes) override;
		virtual bool canWrite(bytesize_t numBytes, bool autoExpand = false) override;
		virtual bool clear() override;

		bool open(const char* path, bool readonly);
		void close();

		bool isOpen();

		FILE* rawHandle();

		File& operator=(File &&other);

		static bool exists(const char* path);

	private:
		FILE* mFile;
	};
}

#endif // _SERIALIZE_FILE_H_