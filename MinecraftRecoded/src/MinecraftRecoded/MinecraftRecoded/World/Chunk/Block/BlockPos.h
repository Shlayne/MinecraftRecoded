#pragma once

#include <Engine/Core/Int.h>
#include "World/Chunk/ChunkConstants.h"
#include "World/Entity/EntityPos.h"

namespace mcr
{
	struct BlockPos
	{
	public:
		static_assert(s_ChunkBlockSize == 16ll, "BlockPos' bit optimizations require s_ChunkBlockSize to be 16.");
		static_assert(-1 >> 1 == -1, "Compiler uses logical shift instead of arithmetic shift for signed integrals.");
	public:
		constexpr BlockPos(const glm::s64vec3& position = glm::s64vec3(0ll)) noexcept;
		constexpr BlockPos(const BlockPos&) noexcept = default;
		constexpr BlockPos& operator=(const BlockPos&) noexcept = default;
	public:
		constexpr glm::u8vec3 GetLocalPosition() const noexcept;
		constexpr glm::s64vec3 GetChunkPosition() const noexcept;
		constexpr operator EntityPos() const noexcept;
	public:
		constexpr BlockPos  operator+ (const BlockPos& blockPos) const noexcept;
		constexpr BlockPos& operator+=(const BlockPos& blockPos) noexcept;
		constexpr BlockPos  operator+ () const noexcept;
		constexpr BlockPos  operator- (const BlockPos& blockPos) const noexcept;
		constexpr BlockPos& operator-=(const BlockPos& blockPos) noexcept;
		constexpr BlockPos  operator- () const noexcept;
	private:
		glm::s64vec3 m_Position;
	};
}

#include "BlockPos.inl"
