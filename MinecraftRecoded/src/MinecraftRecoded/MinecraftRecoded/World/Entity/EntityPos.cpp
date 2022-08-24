#include "MinecraftRecoded/pch.h"
#include "EntityPos.h"

namespace mcr
{
	EntityPos::EntityPos(const glm::vec3& localPosition, const glm::s64vec3& chunkPosition)
		: x(localPosition.x), y(localPosition.y), z(localPosition.z), m_ChunkPosition(chunkPosition)
	{
		Normalize();
	}

	EntityPos EntityPos::operator+(const EntityPos& entityPos) const noexcept
	{
		return EntityPos(*this) += entityPos;
	}

	EntityPos& EntityPos::operator+=(const EntityPos& entityPos) noexcept
	{
		GetLocalPositionInternal() += entityPos.GetLocalPositionInternal();
		m_ChunkPosition += entityPos.m_ChunkPosition;
		Normalize();
		return *this;
	}

	EntityPos EntityPos::operator+() const noexcept
	{
		return EntityPos(+GetLocalPositionInternal(), +m_ChunkPosition);
	}

	EntityPos EntityPos::operator-(const EntityPos& entityPos) const noexcept
	{
		return EntityPos(*this) -= entityPos;
	}

	EntityPos& EntityPos::operator-=(const EntityPos& entityPos) noexcept
	{
		GetLocalPositionInternal() -= entityPos.GetLocalPositionInternal();
		m_ChunkPosition -= entityPos.m_ChunkPosition;
		Normalize();
		return *this;
	}

	EntityPos EntityPos::operator-() const noexcept
	{
		return EntityPos(-GetLocalPositionInternal(), -m_ChunkPosition);
	}

	glm::vec3& EntityPos::GetLocalPositionInternal() const noexcept
	{
		return *(glm::vec3*)&x;
	}

	// Normalizes the EntityPos's local position into [0.0f, s_ChunkBlockSize)
	// and puts the excess position information in its chunk position.
	void EntityPos::Normalize() noexcept
	{
		glm::vec3 excessChunkPosition = glm::floor(GetLocalPosition() / static_cast<float>(s_ChunkBlockSize));
		m_ChunkPosition += excessChunkPosition;
		GetLocalPositionInternal() -= static_cast<float>(s_ChunkBlockSize) * excessChunkPosition;
	}
}
