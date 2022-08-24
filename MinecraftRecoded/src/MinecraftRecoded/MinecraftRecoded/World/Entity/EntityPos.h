#pragma once

#include <Engine/Core/Int.h>
#include "World/Chunk/ChunkConstants.h"
#include "MinecraftRecoded/Util/PrimitiveWrapper.h"

namespace mcr
{
	struct EntityPos
	{
	public:
		constexpr EntityPos() noexcept = default;
		EntityPos(const glm::vec3& localPosition, const glm::s64vec3& chunkPosition = glm::s64vec3(0ull));
	public:
		constexpr glm::vec3 GetLocalPosition() const noexcept;
		constexpr glm::s64vec3 GetChunkPosition() const noexcept;
	public:
		EntityPos  operator+ (const EntityPos& entityPos) const noexcept;
		EntityPos& operator+=(const EntityPos& entityPos) noexcept;
		EntityPos  operator+ () const noexcept;
		EntityPos  operator- (const EntityPos& entityPos) const noexcept;
		EntityPos& operator-=(const EntityPos& entityPos) noexcept;
		EntityPos  operator- () const noexcept;
	private:
		glm::vec3& GetLocalPositionInternal() const noexcept;
		void Normalize() noexcept;
		template<uint8 Coord>
		constexpr void Normalize(float& coordValue) noexcept;
	private:
		template<uint8 Coord>
		struct Coordinate : public PrimitiveWrapper<float>
		{
		public:
			constexpr Coordinate() noexcept = default;
			template<typename T2, typename = std::enable_if_t<std::is_convertible_v<T2, Value>>>
			constexpr Coordinate(T2 value) noexcept;
		public:
			Value operator+(Value value) const noexcept;
			Coordinate& operator+=(Value value) noexcept;
			Value operator-(Value value) const noexcept;
			Coordinate& operator-=(Value value) noexcept;
			Value operator*(Value value) const noexcept;
			Coordinate& operator*=(Value value) noexcept;
			Value operator/(Value value) const noexcept;
			Coordinate& operator/=(Value value) noexcept;
		public:
			template<typename T2, typename = std::enable_if_t<std::is_convertible_v<T2, Value>>>
			Value operator+(T2 value) const noexcept;
			template<typename T2, typename = std::enable_if_t<std::is_convertible_v<T2, Value>>>
			Value operator-(T2 value) const noexcept;
			template<typename T2, typename = std::enable_if_t<std::is_convertible_v<T2, Value>>>
			Value operator*(T2 value) const noexcept;
			template<typename T2, typename = std::enable_if_t<std::is_convertible_v<T2, Value>>>
			Value operator/(T2 value) const noexcept;
		public:
			Value operator++(int) noexcept;
			Coordinate& operator++() noexcept;
			Value operator--(int) noexcept;
			Coordinate& operator--() noexcept;
		private:
			void Normalize() noexcept;
		};
	public:
		Coordinate<0> x;
		Coordinate<1> y;
		Coordinate<2> z;
	private:
		glm::s64vec3 m_ChunkPosition{ 0ll };
	};
}

#include "EntityPos.inl"
