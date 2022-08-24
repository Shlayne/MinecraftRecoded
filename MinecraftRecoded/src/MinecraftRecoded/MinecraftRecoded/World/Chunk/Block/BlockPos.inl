namespace mcr
{
	constexpr BlockPos::BlockPos(const glm::s64vec3& position) noexcept
		: x(position.x), y(position.y), z(position.z) {}

	constexpr glm::u8vec3 BlockPos::GetLocalPosition() const noexcept
	{
		return static_cast<glm::s64vec3>(*this) % s_ChunkBlockSize;
	}

	constexpr glm::s64vec3 BlockPos::GetChunkPosition() const noexcept
	{
		return static_cast<glm::s64vec3>(*this) / s_ChunkBlockSize;
	}

	constexpr BlockPos BlockPos::operator+() const noexcept
	{
		return BlockPos(+static_cast<glm::s64vec3>(*this));
	}

	constexpr BlockPos BlockPos::operator-() const noexcept
	{
		return BlockPos(-static_cast<glm::s64vec3>(*this));
	}

	constexpr BlockPos::operator glm::s64vec3() const noexcept
	{
		return glm::s64vec3(x, y, z);
	}
}
