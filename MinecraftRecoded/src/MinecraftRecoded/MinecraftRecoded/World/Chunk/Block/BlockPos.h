#pragma once

#include <Engine/Core/Int.h>
#include "World/Chunk/ChunkConstants.h"
#include "World/Entity/EntityPos.h"

namespace mcr
{
	struct BlockPos : private glm::s64vec3
	{
	public:
		constexpr BlockPos(const glm::s64vec3& position = glm::s64vec3(0ll)) noexcept;
	public:
		constexpr glm::u8vec3 GetLocalPosition() const noexcept;
		constexpr glm::s64vec3 GetChunkPosition() const noexcept;
	public:
		constexpr BlockPos  operator+ (const BlockPos& blockPos) const noexcept;
		constexpr BlockPos& operator+=(const BlockPos& blockPos) noexcept;
		constexpr BlockPos  operator+() const noexcept;
		constexpr BlockPos  operator- (const BlockPos& blockPos) const noexcept;
		constexpr BlockPos& operator-=(const BlockPos& blockPos) noexcept;
		constexpr BlockPos  operator-() const noexcept;
	public:
		constexpr operator glm::s64vec3() const noexcept;
		constexpr operator EntityPos() const noexcept;
	public:
		using glm::s64vec3::x;
		using glm::s64vec3::y;
		using glm::s64vec3::z;
	};
}

#include "BlockPos.inl"
