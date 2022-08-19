#pragma once

#include <Engine/Core/Int.h>
#include "World/Chunk/ChunkConstants.h"

namespace mcr
{
	struct EntityPos
	{
	public:
		constexpr EntityPos(const glm::vec3& localPosition = glm::vec3(0.0f), const glm::s64vec3& chunkPosition = glm::s64vec3(0ull));
		constexpr EntityPos(const EntityPos&) noexcept = default;
		constexpr EntityPos& operator=(const EntityPos&) noexcept = default;
	public:
		constexpr glm::vec3 GetLocalPosition() const noexcept;
		constexpr glm::s64vec3 GetChunkPosition() const noexcept;
	public:
		constexpr EntityPos  operator+ (const EntityPos& entityPos) const noexcept;
		constexpr EntityPos& operator+=(const EntityPos& entityPos) noexcept;
		constexpr EntityPos  operator+ () const noexcept;
		constexpr EntityPos  operator- (const EntityPos& entityPos) const noexcept;
		constexpr EntityPos& operator-=(const EntityPos& entityPos) noexcept;
		constexpr EntityPos  operator- () const noexcept;
	private:
		constexpr void Normalize() noexcept;
	private:
		glm::vec3 m_LocalPosition;
		glm::s64vec3 m_ChunkPosition;
	};
}

#include "EntityPos.inl"
