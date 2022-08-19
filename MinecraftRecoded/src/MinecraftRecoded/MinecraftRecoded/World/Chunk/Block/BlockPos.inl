namespace mcr
{
	constexpr BlockPos::BlockPos(const glm::s64vec3& position) noexcept
		: m_Position(position) {}

	constexpr glm::u8vec3 BlockPos::GetLocalPosition() const noexcept
	{
		return m_Position & 0xFll;
	}

	constexpr glm::s64vec3 BlockPos::GetChunkPosition() const noexcept
	{
		return m_Position >> 4ll;
	}

	constexpr BlockPos::operator EntityPos() const noexcept
	{
		return EntityPos(GetLocalPosition(), GetChunkPosition());
	}

	constexpr BlockPos BlockPos::operator+(const BlockPos& blockPos) const noexcept
	{
		return +*this += blockPos;
	}

	constexpr BlockPos& BlockPos::operator+=(const BlockPos& blockPos) noexcept
	{
		m_Position += blockPos.m_Position;
		return *this;
	}

	constexpr BlockPos BlockPos::operator+() const noexcept
	{
		return BlockPos(+m_Position);
	}

	constexpr BlockPos BlockPos::operator-(const BlockPos& blockPos) const noexcept
	{
		return +*this -= blockPos;
	}

	constexpr BlockPos& BlockPos::operator-=(const BlockPos& blockPos) noexcept
	{
		m_Position -= blockPos.m_Position;
		return *this;
	}

	constexpr BlockPos BlockPos::operator-() const noexcept
	{
		return BlockPos(-m_Position);
	}
}
