#ifndef _SERIALIZE_TYPES_H_
#define _SERIALIZE_TYPES_H_

#include "Config.h"

#include <cstdint>

namespace Serialize
{
	typedef float float32_t;
	typedef double float64_t;

	// Types to support bytestream metrics
	typedef uint32_t seek_t;
	typedef uint32_t bytesize_t;
}

#endif // _SERIALIZE_TYPES_H_