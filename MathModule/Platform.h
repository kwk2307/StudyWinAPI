#pragma once

#include "CoreDefinition.h"

//#define PLATFORM_WINDOWS 1;

#if defined(PLATFORM_WINDOWS)
#include "WindowsPlatform.h"
#endif

#if !defined(FORCEINLINE)
#define FORCEINLINE inline
#endif

