#pragma once

#ifdef GEL_BUILD_DLL
	#define GEL_API __declspec(dllexport)
#else
	#define GEL_API __declspec(dllimport)
#endif