#pragma once

#include <Engine/Core/Int.h>
#include "World/Chunk/ChunkConstants.h"

namespace mcr
{
	// This is required to get the normalize functionality integrated into the component's operators.
	struct EntityPosFloatWrapper
	{
	public:
		constexpr EntityPosFloatWrapper(float local = 0.0f, sint64 chunk = 0ll) noexcept;
		constexpr EntityPosFloatWrapper(const EntityPosFloatWrapper&) noexcept = default;
		constexpr EntityPosFloatWrapper& operator=(const EntityPosFloatWrapper&) noexcept = default;
	public:
		constexpr EntityPosFloatWrapper  operator+ (EntityPosFloatWrapper value) const noexcept;
		constexpr EntityPosFloatWrapper& operator+=(EntityPosFloatWrapper value) noexcept;
		constexpr EntityPosFloatWrapper  operator- (EntityPosFloatWrapper value) const noexcept;
		constexpr EntityPosFloatWrapper& operator-=(EntityPosFloatWrapper value) noexcept;
		constexpr EntityPosFloatWrapper  operator* (EntityPosFloatWrapper value) const noexcept;
		constexpr EntityPosFloatWrapper& operator*=(EntityPosFloatWrapper value) noexcept;
		constexpr EntityPosFloatWrapper  operator/ (EntityPosFloatWrapper value) const noexcept;
		constexpr EntityPosFloatWrapper& operator/=(EntityPosFloatWrapper value) noexcept;
	public:
		constexpr EntityPosFloatWrapper  operator+ () const noexcept;
		constexpr EntityPosFloatWrapper  operator- () const noexcept;
	public:
		constexpr EntityPosFloatWrapper  operator++(int) const noexcept;
		constexpr EntityPosFloatWrapper& operator++() noexcept;
		constexpr EntityPosFloatWrapper  operator--(int) const noexcept;
		constexpr EntityPosFloatWrapper& operator--() noexcept;
	private:
		friend struct EntityPos;

		constexpr void Normalize() noexcept;

		// I can't believe I didn't think to combine them instead of doing crazy non-constexpr unsafe memory address offsets.
		float m_Local;
		sint64 m_Chunk;
	};

	struct EntityPos : private glm::vec<3, EntityPosFloatWrapper>
	{
	public:
		constexpr EntityPos() noexcept;
		constexpr EntityPos(const glm::vec3& localPosition, const glm::s64vec3& chunkPosition = glm::s64vec3(0ull)) noexcept;
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
		using Wrapper = EntityPosFloatWrapper;
		using Base = glm::vec<3, Wrapper>;

		constexpr void Normalize() noexcept;
		constexpr EntityPos(const Base& base) noexcept;
	public:
		using Base::x;
		using Base::y;
		using Base::z;
	};
}

#include "EntityPos.inl"
