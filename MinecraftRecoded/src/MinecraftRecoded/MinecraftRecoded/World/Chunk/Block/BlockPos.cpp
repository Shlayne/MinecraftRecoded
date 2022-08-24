#include "MinecraftRecoded/pch.h"
#include "BlockPos.h"

namespace mcr
{
	BlockPos BlockPos::operator+(const BlockPos& blockPos) const noexcept
	{
		return BlockPos(*this) += blockPos;
	}

	BlockPos& BlockPos::operator+=(const BlockPos& blockPos) noexcept
	{
		GetChunkPositionInternal() += static_cast<glm::s64vec3>(blockPos);
		return *this;
	}

	BlockPos BlockPos::operator-(const BlockPos& blockPos) const noexcept
	{
		return BlockPos(*this) -= blockPos;
	}

	BlockPos& BlockPos::operator-=(const BlockPos& blockPos) noexcept
	{
		GetChunkPositionInternal() -= static_cast<glm::s64vec3>(blockPos);
		return *this;
	}

	BlockPos::operator EntityPos() const noexcept
	{
		return EntityPos(GetLocalPosition(), GetChunkPosition());
	}

	glm::s64vec3& BlockPos::GetChunkPositionInternal() const noexcept
	{
		return *(glm::s64vec3*)&x;
	}
}
