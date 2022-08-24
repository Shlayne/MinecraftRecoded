namespace mcr
{
	constexpr glm::vec3 EntityPos::GetLocalPosition() const noexcept
	{
		return glm::vec3(x, y, z);
	}

	constexpr glm::s64vec3 EntityPos::GetChunkPosition() const noexcept
	{
		return m_ChunkPosition;
	}

	// Does the same as the Normalize defined in EntityPos.cpp, but for only one coordinate.
	template<uint8 Coord>
	constexpr void EntityPos::Normalize(float& coordValue) noexcept
	{
		float excessChunkCoord = gcem::floor(coordValue / static_cast<float>(s_ChunkBlockSize));
		m_ChunkPosition[Coord] += static_cast<sint64>(excessChunkCoord);
		coordValue -= static_cast<float>(s_ChunkBlockSize) * excessChunkCoord;
	}

	template<uint8 Coord>
	template<typename T2, typename>
	constexpr EntityPos::Coordinate<Coord>::Coordinate(T2 value) noexcept
		: PrimitiveWrapper(value) {}

	template<uint8 Coord>
	EntityPos::Coordinate<Coord>::Value EntityPos::Coordinate<Coord>::operator+(Value value) const noexcept
	{
		return Coordinate(*this) += value;
	}

	template<uint8 Coord>
	EntityPos::Coordinate<Coord>& EntityPos::Coordinate<Coord>::operator+=(Value value) noexcept
	{
		m_Value += value;
		Normalize();
		return *this;
	}

	template<uint8 Coord>
	EntityPos::Coordinate<Coord>::Value EntityPos::Coordinate<Coord>::operator-(Value value) const noexcept
	{
		return Coordinate(*this) -= value;
	}

	template<uint8 Coord>
	EntityPos::Coordinate<Coord>& EntityPos::Coordinate<Coord>::operator-=(Value value) noexcept
	{
		m_Value -= value;
		Normalize();
		return *this;
	}

	template<uint8 Coord>
	EntityPos::Coordinate<Coord>::Value EntityPos::Coordinate<Coord>::operator*(Value value) const noexcept
	{
		return Coordinate(*this) *= value;
	}

	template<uint8 Coord>
	EntityPos::Coordinate<Coord>& EntityPos::Coordinate<Coord>::operator*=(Value value) noexcept
	{
		m_Value *= value;
		Normalize();
		return *this;
	}

	template<uint8 Coord>
	EntityPos::Coordinate<Coord>::Value EntityPos::Coordinate<Coord>::operator/(Value value) const noexcept
	{
		return Coordinate(*this) /= value;
	}

	template<uint8 Coord>
	EntityPos::Coordinate<Coord>& EntityPos::Coordinate<Coord>::operator/=(Value value) noexcept
	{
		m_Value /= value;
		Normalize();
		return *this;
	}

	template<uint8 Coord>
	template<typename T2, typename>
	EntityPos::Coordinate<Coord>::Value EntityPos::Coordinate<Coord>::operator+(T2 value) const noexcept
	{
		return *this + static_cast<Value>(value);
	}

	template<uint8 Coord>
	template<typename T2, typename>
	EntityPos::Coordinate<Coord>::Value EntityPos::Coordinate<Coord>::operator-(T2 value) const noexcept
	{
		return *this - static_cast<Value>(value);
	}

	template<uint8 Coord>
	template<typename T2, typename>
	EntityPos::Coordinate<Coord>::Value EntityPos::Coordinate<Coord>::operator*(T2 value) const noexcept
	{
		return *this * static_cast<Value>(value);
	}

	template<uint8 Coord>
	template<typename T2, typename>
	EntityPos::Coordinate<Coord>::Value EntityPos::Coordinate<Coord>::operator/(T2 value) const noexcept
	{
		return *this / static_cast<Value>(value);
	}

	template<uint8 Coord>
	EntityPos::Coordinate<Coord>::Value EntityPos::Coordinate<Coord>::operator++(int) noexcept
	{
		Value value = m_Value;
		++*this;
		return value;
	}

	template<uint8 Coord>
	EntityPos::Coordinate<Coord>& EntityPos::Coordinate<Coord>::operator++() noexcept
	{
		++m_Value;
		Normalize();
		return *this;
	}

	template<uint8 Coord>
	EntityPos::Coordinate<Coord>::Value EntityPos::Coordinate<Coord>::operator--(int) noexcept
	{
		Value value = m_Value;
		--*this;
		return value;
	}

	template<uint8 Coord>
	EntityPos::Coordinate<Coord>& EntityPos::Coordinate<Coord>::operator--() noexcept
	{
		--m_Value;
		Normalize();
		return *this;
	}

	template<uint8 Coord>
	void EntityPos::Coordinate<Coord>::Normalize() noexcept
	{
		// This is why the other methods aren't constexpr.
		reinterpret_cast<EntityPos*>(this - Coord)->Normalize<Coord>(m_Value);
	}
}
