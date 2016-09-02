#ifndef _SERIALIZE_CONFIG_H_
#define _SERIALIZE_CONFIG_H_

#if defined(_WIN32) && defined(SERIALIZE_DYNAMIC)
#	if defined(SERIALIZE_COMPILE)
#		define SERIALIZE_EXPORT __declspec(dllexport)
#	else
#		define SERIALIZE_EXPORT __declspec(dllimport)
#	endif
#else
#	define SERIALIZE_EXPORT
#endif

#endif // _SERIALIZE_CONFIG_H_