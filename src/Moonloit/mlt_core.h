#pragma once

#ifdef MLT_PLATFORM_WINDOWS
	#ifdef MLT_BUILD_SHARED
		#define MOONLOIT_API __declspec(dllexport)
	#elif MLT_IMPORT_SHARED
		#define MOONLOIT_API __declspec(dllimport)
	#else // building or using static lib
		#define MOONLOIT_API 
	#endif
#elif MLT_PLATFORM_LINUX
	#ifdef MLT_SHARED_LIB
		#define MOONLOIT_API __attribute__((visibility("default")))
	#else
		#define MOONLOIT_API 
	#endif
#endif

#ifdef MLT_ASSERTIONS_ENABLED
	#define MOONLOIT_ASSERT(x, ...) { if (!(x)) { throw std::runtime_error(__VA_ARGS__); } }
#else
	#define MOONLOIT_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)