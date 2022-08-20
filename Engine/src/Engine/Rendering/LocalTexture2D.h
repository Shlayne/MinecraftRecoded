#pragma once

#include "Engine/Core/Core.h"
#include <string_view>

namespace eng
{
	class LocalTexture2D
	{
	public:
		constexpr LocalTexture2D() = default;
		LocalTexture2D(std::string_view filepath, sint32 requiredChannels = 0);
		LocalTexture2D(std::string_view filepath, bool flipVertically, sint32 requiredChannels = 0);
		LocalTexture2D(sint32 width, sint32 height, sint32 channels);
		LocalTexture2D(const LocalTexture2D& texture);
		LocalTexture2D(LocalTexture2D&& texture) noexcept;
		LocalTexture2D& operator=(const LocalTexture2D& texture);
		LocalTexture2D& operator=(LocalTexture2D&& texture) noexcept;
		~LocalTexture2D();

		bool ReadFile(std::string_view filepath, sint32 requiredChannels = 0);
		bool ReadFile(std::string_view filepath, bool flipVertically, sint32 requiredChannels = 0);
		bool WriteFile(std::string_view filepath);
		bool WriteFile(std::string_view filepath, bool flipVertically);

		bool SetSubregion(const LocalTexture2D& texture, sint32 positionX, sint32 positionY);

		constexpr std::string_view GetFilepath() const noexcept { return m_Filepath; }
		constexpr sint32 GetWidth() const noexcept { return m_Width; }
		constexpr sint32 GetHeight() const noexcept { return m_Height; }
		constexpr sint32 GetChannels() const noexcept { return m_Channels; }
		constexpr uint8* GetData() const noexcept { return m_Data; }

		constexpr operator bool() const noexcept { return m_Data != nullptr; }
		constexpr bool operator==(const LocalTexture2D& texture) const noexcept { return m_Data == texture.m_Data; }

		static Ref<LocalTexture2D> CreateRef();
		static Ref<LocalTexture2D> CreateRef(std::string_view filepath, sint32 requiredChannels = 0);
		static Ref<LocalTexture2D> CreateRef(std::string_view filepath, bool flipVertically, sint32 requiredChannels = 0);
		static Ref<LocalTexture2D> CreateRef(sint32 width, sint32 height, sint32 channels);
	private:
		std::string_view m_Filepath;

		sint32 m_Width = 0;
		sint32 m_Height = 0;
		sint32 m_Channels = 0;
		uint8* m_Data = nullptr;
	};
}
