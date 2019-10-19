#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>



#define EXPORT __declspec(dllexport)

#ifdef __cplusplus
extern "C"
{
#endif

	EXPORT void Run(void);
#ifdef __cplusplus
}
#endif