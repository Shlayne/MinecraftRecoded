#pragma once

#include <glm/glm.hpp>
#include <gcem.hpp>
#include <cstdint>

using sint8  = int8_t;
using sint16 = int16_t;
using sint32 = int32_t;
using sint64 = int64_t;

using uint8  = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

constexpr inline sint8  sint8_min  = static_cast<sint8 >(0x80);
constexpr inline sint16 sint16_min = static_cast<sint16>(0x8000);
constexpr inline sint32 sint32_min = static_cast<sint32>(0x80000000);
constexpr inline sint64 sint64_min = static_cast<sint64>(0x8000000000000000);

constexpr inline sint8  sint8_max  = static_cast<sint8 >(0x7F);
constexpr inline sint16 sint16_max = static_cast<sint16>(0x7FFF);
constexpr inline sint32 sint32_max = static_cast<sint32>(0x7FFFFFFF);
constexpr inline sint64 sint64_max = static_cast<sint64>(0x7FFFFFFFFFFFFFFF);

constexpr inline uint8  uint8_max  = static_cast<uint8 >(0xFF);
constexpr inline uint16 uint16_max = static_cast<uint16>(0xFFFF);
constexpr inline uint32 uint32_max = static_cast<uint32>(0xFFFFFFFF);
constexpr inline uint64 uint64_max = static_cast<uint64>(0xFFFFFFFFFFFFFFFF);

namespace glm
{
	using s8vec1 = i8vec1;
	using s16vec1 = i16vec1;
	using s32vec1 = i32vec1;
	using s64vec1 = i64vec1;

	using s8vec2  = i8vec2;
	using s16vec2 = i16vec2;
	using s32vec2 = i32vec2;
	using s64vec2 = i64vec2;

	using s8vec3 = i8vec3;
	using s16vec3 = i16vec3;
	using s32vec3 = i32vec3;
	using s64vec3 = i64vec3;

	using s8vec4 = i8vec4;
	using s16vec4 = i16vec4;
	using s32vec4 = i32vec4;
	using s64vec4 = i64vec4;
}
