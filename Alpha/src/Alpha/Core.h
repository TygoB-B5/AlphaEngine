#pragma once

#ifndef AP_PLATFORM_WINDOWS
	#error Alpha only supports windows!
#endif

#ifdef AP_ENABLE_ASSERTS
	#define AP_ASSERT(x, ...) { if(!x) {AP_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define AP_CORE_ASSERT(x, ...) { if(!x) {AP_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define AP_ASSERT(x, ...)
	#define AP_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define AP_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)