#ifndef PLATFORM_LIBRARY_H
#define PLATFORM_LIBRARY_H

#include "definitions.h"

#define PLATFORM_API

#define Print(format, ...) do { char _buffer[1024]; PlatformFormatString(_buffer, sizeof(_buffer), format, __VA_ARGS__); PlatformWriteConsole(_buffer, (u32)PlatformStringLength(_buffer)); } while(0)
#define Log(format, ...) Print(format, __VA_ARGS__)

#endif