namespace mcr
{
	constexpr EntityPosFloatWrapper::EntityPosFloatWrapper(float local, sint64 chunk) noexcept
		: m_Local(local), m_Chunk(chunk) {}

	constexpr EntityPosFloatWrapper EntityPosFloatWrapper::operator+(EntityPosFloatWrapper value) const noexcept
	{
		return +*this += value;
	}

	constexpr EntityPosFloatWrapper& EntityPosFloatWrapper::operator+=(EntityPosFloatWrapper value) noexcept
	{
		m_Local += value.m_Local;
		m_Chunk += value.m_Chunk;
		Normalize();
		return *this;
	}

	constexpr EntityPosFloatWrapper EntityPosFloatWrapper::operator-(EntityPosFloatWrapper value) const noexcept
	{
		return +*this -= value;
	}

	constexpr EntityPosFloatWrapper& EntityPosFloatWrapper::operator-=(EntityPosFloatWrapper value) noexcept
	{
		m_Local -= value.m_Local;
		m_Chunk -= value.m_Chunk;
		Normalize();
		return *this;
	}

	constexpr EntityPosFloatWrapper EntityPosFloatWrapper::operator*(EntityPosFloatWrapper value) const noexcept
	{
		return +*this *= value;
	}

	constexpr EntityPosFloatWrapper& EntityPosFloatWrapper::operator*=(EntityPosFloatWrapper value) noexcept
	{
		m_Local *= value.m_Local;
		m_Chunk *= value.m_Chunk;
		Normalize();
		return *this;
	}

	constexpr EntityPosFloatWrapper EntityPosFloatWrapper::operator/(EntityPosFloatWrapper value) const noexcept
	{
		return +*this /= value;
	}

	constexpr EntityPosFloatWrapper& EntityPosFloatWrapper::operator/=(EntityPosFloatWrapper value) noexcept
	{
		m_Local /= value.m_Local;
		m_Chunk /= value.m_Chunk;
		Normalize();
		return *this;
	}

	constexpr EntityPosFloatWrapper EntityPosFloatWrapper::operator+() const noexcept
	{
		return EntityPosFloatWrapper(*this);
	}

	constexpr EntityPosFloatWrapper EntityPosFloatWrapper::operator-() const noexcept
	{
		return EntityPosFloatWrapper(-m_Local, -m_Chunk);
	}

	constexpr EntityPosFloatWrapper EntityPosFloatWrapper::operator++(int) const noexcept
	{
		return ++(+*this);
	}

	constexpr EntityPosFloatWrapper& EntityPosFloatWrapper::operator++() noexcept
	{
		m_Local++;
		Normalize();
		return *this;
	}

	constexpr EntityPosFloatWrapper EntityPosFloatWrapper::operator--(int) const noexcept
	{
		return --(+*this);
	}

	constexpr EntityPosFloatWrapper& EntityPosFloatWrapper::operator--() noexcept
	{
		m_Local--;
		Normalize();
		return *this;
	}

	constexpr void EntityPosFloatWrapper::Normalize() noexcept
	{
		float unfloored = m_Local / static_cast<float>(s_ChunkBlockSize);
		float excessChunkPosition = gcem::floor(unfloored);
		m_Chunk += static_cast<sint64>(excessChunkPosition);
		m_Local -= static_cast<float>(s_ChunkBlockSize) * excessChunkPosition;
	}



	constexpr EntityPos::EntityPos() noexcept
		: Base(Wrapper{}) {}

	constexpr EntityPos::EntityPos(const glm::vec3& localPosition, const glm::s64vec3& chunkPosition) noexcept
		: Base(
			Wrapper(localPosition.x, chunkPosition.x),
			Wrapper(localPosition.y, chunkPosition.y),
			Wrapper(localPosition.z, chunkPosition.z))
	{
		Normalize();
	}

	constexpr glm::vec3 EntityPos::GetLocalPosition() const noexcept
	{
		return glm::vec3(x.m_Local, y.m_Local, z.m_Local);
	}

	constexpr glm::s64vec3 EntityPos::GetChunkPosition() const noexcept
	{
		return glm::vec3(x.m_Chunk, y.m_Chunk, z.m_Chunk);
	}

	constexpr EntityPos EntityPos::operator+(const EntityPos& entityPos) const noexcept
	{
		return +*this += entityPos;
	}

	constexpr EntityPos& EntityPos::operator+=(const EntityPos& entityPos) noexcept
	{
		Base::operator+=(static_cast<Base>(entityPos));
		Normalize();
		return *this;
	}

	constexpr EntityPos EntityPos::operator+() const noexcept
	{
		return EntityPos(*this);
	}

	constexpr EntityPos EntityPos::operator-(const EntityPos& entityPos) const noexcept
	{
		return +*this -= entityPos;
	}

	constexpr EntityPos& EntityPos::operator-=(const EntityPos& entityPos) noexcept
	{
		Base::operator-=(static_cast<Base>(entityPos));
		Normalize();
		return *this;
	}

	constexpr EntityPos EntityPos::operator-() const noexcept
	{
		return glm::operator-(static_cast<Base>(*this));
	}

	// Normalizes the EntityPos's local position into [0.0f, s_ChunkBlockSize)
	// and puts the excess position information in its chunk position.
	constexpr void EntityPos::Normalize() noexcept
	{
		x.Normalize();
		y.Normalize();
		z.Normalize();
	}

	constexpr EntityPos::EntityPos(const Base& base) noexcept
		: Base(base) {}
}
