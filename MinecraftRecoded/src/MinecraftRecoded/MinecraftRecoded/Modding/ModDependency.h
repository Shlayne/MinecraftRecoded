#pragma once

#include <Engine/Core/Int.h>
#include <compare>
#include <string_view>

namespace mcr
{
	struct ModVersion
	{
	public:
		constexpr ModVersion() noexcept = default;
		constexpr ModVersion(uint8 major, uint8 minor, uint16 patch) noexcept;
		constexpr ModVersion(const ModVersion&) noexcept = default;
		constexpr ModVersion& operator=(const ModVersion&) noexcept = default;
	public:
		constexpr std::strong_ordering operator<=>(ModVersion version) const noexcept;
	public:
		constexpr uint8 GetMajor() const noexcept;
		constexpr uint8 GetMinor() const noexcept;
		constexpr uint16 GetPatch() const noexcept;
	private:
		uint8 m_Major = 0;
		uint8 m_Minor = 0;
		uint16 m_Patch = 0;
	};

	struct ModVersionRange
	{
	public:
		constexpr ModVersionRange() noexcept = default;
		constexpr ModVersionRange(ModVersion minVersion, ModVersion maxVersion, bool inclusive = false) noexcept;
		constexpr ModVersionRange(const ModVersionRange&) noexcept = default;
		constexpr ModVersionRange& operator=(const ModVersionRange&) noexcept = default;
	public:
		constexpr bool Contains(ModVersion version) const noexcept;
	public:
		constexpr ModVersion GetMinVersion() const noexcept;
		constexpr ModVersion GetMaxVersion() const noexcept;
		constexpr bool IsInclusive() const noexcept;
	private:
		ModVersion m_MinVersion;
		ModVersion m_MaxVersion;
		bool m_Inclusive = false;
	};

	using ModDependencyType_ = uint8;
	enum ModDependencyType : ModDependencyType_
	{
		// If not present, cause overall mod loading to fail.
		ModDependencyType_HardRequired,

		// If not present, load this mod without some functionality.
		ModDependencyType_Optional,

		// If not present, don't load this mod.
		ModDependencyType_SoftRequired,

		// Default is hard required.
		ModDependencyType_Default = ModDependencyType_HardRequired
	};

	struct ModDependency
	{
	public:
		constexpr ModDependency() noexcept = default;
		constexpr ModDependency(std::string_view modID, ModVersionRange versionRange, ModDependencyType type) noexcept;
		constexpr ModDependency(const ModDependency&) noexcept = default;
		constexpr ModDependency& operator=(const ModDependency&) noexcept = default;
	public:
		constexpr std::string_view GetModID() const noexcept;
		constexpr ModVersionRange GetVersionRange() const noexcept;
		constexpr ModDependencyType GetType() const noexcept;
	private:
		std::string_view m_ModID;
		ModVersionRange m_VersionRange;
		ModDependencyType m_Type = ModDependencyType_Default;
	};
}

#include "ModDependency.inl"
