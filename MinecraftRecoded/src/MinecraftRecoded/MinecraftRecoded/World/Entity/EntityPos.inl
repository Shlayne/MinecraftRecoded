namespace mcr
{
	constexpr EntityPos::EntityPos(const glm::vec3& crLocalPosition, const glm::s64vec3& crChunkPosition)
		: m_LocalPosition(crLocalPosition), m_ChunkPosition(crChunkPosition)
	{
		Normalize();
	}

	constexpr glm::vec3 EntityPos::GetLocalPosition() const noexcept
	{
		return m_LocalPosition;
	}

	constexpr glm::s64vec3 EntityPos::GetChunkPosition() const noexcept
	{
		return m_ChunkPosition;
	}

	constexpr EntityPos EntityPos::operator+(const EntityPos& entityPos) const noexcept
	{
		return +*this += entityPos;
	}

	constexpr EntityPos& EntityPos::operator+=(const EntityPos& entityPos) noexcept
	{
		m_LocalPosition += entityPos.m_LocalPosition;
		m_ChunkPosition += entityPos.m_ChunkPosition;
		Normalize();
		return *this;
	}

	constexpr EntityPos EntityPos::operator+() const noexcept
	{
		return EntityPos(+m_LocalPosition, +m_ChunkPosition);
	}

	constexpr EntityPos EntityPos::operator-(const EntityPos& entityPos) const noexcept
	{
		return +*this -= entityPos;
	}

	constexpr EntityPos& EntityPos::operator-=(const EntityPos& entityPos) noexcept
	{
		m_LocalPosition -= entityPos.m_LocalPosition;
		m_ChunkPosition -= entityPos.m_ChunkPosition;
		Normalize();
		return *this;
	}

	constexpr EntityPos EntityPos::operator-() const noexcept
	{
		return EntityPos(-m_LocalPosition, -m_ChunkPosition);
	}
}

// I hate how legacy code backwards compatability is the only thing holding back
// math functions from being constexpr. They once thought it was a good idea for
// a math function to modify errno on error. What kind of absolutely stupid fuc-
namespace glm
{
	namespace detail
	{
		template<length_t L, typename T, qualifier Q, bool Aligned>
		struct compute_gcem_floor
		{
			GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<L, T, Q> call(vec<L, T, Q> const& x)
			{
				return detail::functor1<vec, L, T, T, Q>::call(gcem::floor, x);
			}
		};
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, T, Q> gcem_floor(vec<L, T, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'floor' only accept floating-point inputs.");
		return detail::compute_gcem_floor<L, T, Q, detail::is_aligned<Q>::value>::call(x);
	}
}

namespace mcr
{
	// Normalizes the EntityPos's local position into [0.0f, s_ChunkBlockSize)
	// and puts the excess position information in its chunk position.
	constexpr void EntityPos::Normalize() noexcept
	{
		glm::vec3 excessChunkPosition = glm::gcem_floor(m_LocalPosition / static_cast<float>(s_ChunkBlockSize));
		m_ChunkPosition += excessChunkPosition;
		m_LocalPosition -= static_cast<float>(s_ChunkBlockSize) * excessChunkPosition;
	}
}
