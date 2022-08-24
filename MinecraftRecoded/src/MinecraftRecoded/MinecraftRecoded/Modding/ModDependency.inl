namespace mcr
{
	constexpr ModVersion::ModVersion(uint8 major, uint8 minor, uint16 patch) noexcept
		: m_Major(major), m_Minor(minor), m_Patch(patch) {}

	constexpr std::strong_ordering ModVersion::operator<=>(ModVersion version) const noexcept
	{
		if (std::strong_ordering order = m_Major <=> version.m_Major; order != 0)
			return order;
		if (std::strong_ordering order = m_Minor <=> version.m_Minor; order != 0)
			return order;
		return m_Patch <=> version.m_Patch;
	}

	constexpr uint8 ModVersion::GetMajor() const noexcept
	{
		return m_Major;
	}

	constexpr uint8 ModVersion::GetMinor() const noexcept
	{
		return m_Minor;
	}

	constexpr uint16 ModVersion::GetPatch() const noexcept
	{
		return m_Patch;
	}

	constexpr ModVersionRange::ModVersionRange(ModVersion minVersion, ModVersion maxVersion, bool inclusive) noexcept
		: m_MinVersion(minVersion), m_MaxVersion(maxVersion), m_Inclusive(inclusive) {}

	constexpr bool ModVersionRange::Contains(ModVersion version) const noexcept
	{
		if ((m_MinVersion <=> version) > 0)
			return false;

		std::strong_ordering order = version <=> m_MaxVersion;
		return order < 0 || (m_Inclusive && order == 0);
	}

	constexpr ModVersion ModVersionRange::GetMinVersion() const noexcept
	{
		return m_MinVersion;
	}

	constexpr ModVersion ModVersionRange::GetMaxVersion() const noexcept
	{
		return m_MaxVersion;
	}

	constexpr bool ModVersionRange::GetInclusive() const noexcept
	{
		return m_Inclusive;
	}

	constexpr ModDependency::ModDependency(std::string_view modID, ModVersionRange versionRange, ModDependencyType type) noexcept
		: m_ModID(modID), m_VersionRange(versionRange), m_Type(type) {}

	constexpr std::string_view ModDependency::GetModID() const noexcept
	{
		return m_ModID;
	}

	constexpr ModVersionRange ModDependency::GetVersionRange() const noexcept
	{
		return m_VersionRange;
	}

	constexpr ModDependencyType ModDependency::GetType() const noexcept
	{
		return m_Type;
	}
}
