#pragma once

#include <Engine/Core/Int.h>
#include "World/Chunk/ChunkConstants.h"
#include "World/Entity/EntityPos.h"

namespace mcr
{
	struct BlockPos
	{
	public:
		constexpr BlockPos(const glm::s64vec3& position = glm::s64vec3(0ll)) noexcept;
	public:
		constexpr glm::u8vec3 GetLocalPosition() const noexcept;
		constexpr glm::s64vec3 GetChunkPosition() const noexcept;
	public:
		BlockPos  operator+ (const BlockPos& blockPos) const noexcept;
		BlockPos& operator+=(const BlockPos& blockPos) noexcept;
		BlockPos  operator- (const BlockPos& blockPos) const noexcept;
		BlockPos& operator-=(const BlockPos& blockPos) noexcept;
	public:
		constexpr BlockPos operator+() const noexcept;
		constexpr BlockPos operator-() const noexcept;
	public:
		constexpr operator glm::s64vec3() const noexcept;
		operator EntityPos() const noexcept;
	public:
		sint64 x;
		sint64 y;
		sint64 z;
	private:
		glm::s64vec3& GetChunkPositionInternal() const noexcept;
	};
}

#include "BlockPos.inl"
