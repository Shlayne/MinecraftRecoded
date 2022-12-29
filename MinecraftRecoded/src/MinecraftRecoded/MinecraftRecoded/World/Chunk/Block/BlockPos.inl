namespace mcr
{
	constexpr BlockPos::BlockPos(const glm::s64vec3& position) noexcept
		: glm::s64vec3(position) {}

	constexpr glm::u8vec3 BlockPos::GetLocalPosition() const noexcept
	{
		return *this % s_ChunkBlockSize;
	}

	constexpr glm::s64vec3 BlockPos::GetChunkPosition() const noexcept
	{
		return *this / s_ChunkBlockSize;
	}

	constexpr BlockPos BlockPos::operator+(const BlockPos& blockPos) const noexcept
	{
		return +*this += blockPos;
	}

	constexpr BlockPos& BlockPos::operator+=(const BlockPos& blockPos) noexcept
	{
		glm::s64vec3::operator+=(static_cast<glm::s64vec3>(blockPos));
		return *this;
	}

	constexpr BlockPos BlockPos::operator+() const noexcept
	{
		return glm::operator+(*this);
	}

	constexpr BlockPos BlockPos::operator-(const BlockPos& blockPos) const noexcept
	{
		return +*this -= blockPos;
	}

	constexpr BlockPos& BlockPos::operator-=(const BlockPos& blockPos) noexcept
	{
		glm::s64vec3::operator-=(static_cast<glm::s64vec3>(blockPos));
		return *this;
	}

	constexpr BlockPos BlockPos::operator-() const noexcept
	{
		return glm::operator-(*this);
	}

	constexpr BlockPos::operator glm::s64vec3() const noexcept
	{
		return *this;
	}

	constexpr BlockPos::operator EntityPos() const noexcept
	{
		return EntityPos(GetLocalPosition(), GetChunkPosition());
	}
}
