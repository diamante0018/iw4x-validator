#ifdef _WIN32
#pragma once

#pragma warning(push)

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#else

#include <sys/types.h>
#include <unistd.h>

#endif

// min and max is required by gdi, therefore NOMINMAX won't work
#ifdef max
	#undef max
#endif

#ifdef min
	#undef min
#endif

#include <algorithm>
#include <cassert>
#include <csignal>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <mutex>
#include <random>
#include <ranges>
#include <sstream>
#include <utility>
#include <vector>

#ifdef _WIN32
#pragma comment(lib, "ntdll.lib")
#endif
