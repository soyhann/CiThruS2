#pragma once

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#endif

#if __has_include("NVIDIA_VideoCodec/Include/nvEncodeAPI.h")
#define CITHRUS_NVENC_AVAILABLE
#include "NVIDIA_VideoCodec/Include/nvEncodeAPI.h"
#else
#pragma message (__FILE__ ": warning: NVIDIA Video Codec SDK not found, NVENC HEVC encoding is unavailable")
#endif

#if defined(_WIN32) && defined(CITHRUS_NVENC_AVAILABLE)
#undef UpdateResource
#endif
