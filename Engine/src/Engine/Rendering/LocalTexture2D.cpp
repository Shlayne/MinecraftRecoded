#include "Engine/pch.h"
#include "Engine/Rendering/LocalTexture2D.h"
#include "Engine/Rendering/RendererAPI.h"
#include <stb_image.h>
#include <stb_image_write.h>

namespace eng
{
	static bool GetDefaultVerticalFlip()
	{
		return RendererAPI::GetAPI() == RendererAPI::API_OpenGL;
	}

	LocalTexture2D::LocalTexture2D(std::string_view filepath, sint32 requiredChannels)
	{
		ReadFile(filepath, requiredChannels);
	}

	LocalTexture2D::LocalTexture2D(std::string_view filepath, bool flipVertically, sint32 requiredChannels)
	{
		ReadFile(filepath, flipVertically, requiredChannels);
	}

	LocalTexture2D::LocalTexture2D(sint32 width, sint32 height, sint32 channels)
		: m_Width(width), m_Height(height), m_Channels(channels)
	{
		size_t size = static_cast<size_t>(width) * height * channels;
		m_pData = new uint8[size]{ 0 };
	}

	LocalTexture2D::LocalTexture2D(const LocalTexture2D& crTexture)
		: m_Filepath(crTexture.m_Filepath), m_Width(crTexture.m_Width), m_Height(crTexture.m_Height), m_Channels(crTexture.m_Channels)
	{
		if (crTexture)
		{
			size_t size = static_cast<size_t>(m_Width) * m_Height * m_Channels;
			m_pData = new uint8[size];
			memcpy_s(m_pData, size, crTexture.m_pData, size);
		}
		else
			m_pData = nullptr;
	}

	LocalTexture2D::LocalTexture2D(LocalTexture2D&& rrTexture) noexcept
		: m_Filepath(std::move(rrTexture.m_Filepath)), m_Width(rrTexture.m_Width), m_Height(rrTexture.m_Height), m_Channels(rrTexture.m_Channels), m_pData(rrTexture.m_pData)
	{
		rrTexture.m_Width = 0;
		rrTexture.m_Height = 0;
		rrTexture.m_Channels = 0;
		rrTexture.m_pData = nullptr;
	}

	LocalTexture2D& LocalTexture2D::operator=(const LocalTexture2D& crTexture)
	{
		if (this != &crTexture)
		{
			if (m_pData != nullptr)
				delete[] m_pData;

			m_Width = crTexture.m_Width;
			m_Height = crTexture.m_Height;
			m_Channels = crTexture.m_Channels;
			m_Filepath = crTexture.m_Filepath;

			if (crTexture)
			{
				size_t size = static_cast<size_t>(m_Width) * m_Height * m_Channels;
				m_pData = new uint8[size];
				memcpy_s(m_pData, size, crTexture.m_pData, size);
			}
			else
				m_pData = nullptr;
		}
		return *this;
	}

	LocalTexture2D& LocalTexture2D::operator=(LocalTexture2D&& rrTexture) noexcept
	{
		if (this != &rrTexture)
		{
			m_Filepath = std::move(rrTexture.m_Filepath);
			m_Width = rrTexture.m_Width;
			m_Height = rrTexture.m_Height;
			m_Channels = rrTexture.m_Channels;
			m_pData = rrTexture.m_pData;

			rrTexture.m_Width = 0;
			rrTexture.m_Height = 0;
			rrTexture.m_Channels = 0;
			rrTexture.m_pData = nullptr;
		}
		return *this;
	}

	LocalTexture2D::~LocalTexture2D()
	{
		delete[] m_pData;
	}

	bool LocalTexture2D::ReadFile(std::string_view filepath, sint32 requiredChannels)
	{
		return ReadFile(filepath, GetDefaultVerticalFlip(), requiredChannels);
	}

	bool LocalTexture2D::ReadFile(std::string_view filepath, bool flipVertically, sint32 requiredChannels)
	{
		PROFILE_FUNCTION();

		stbi_set_flip_vertically_on_load(flipVertically);
		stbi_uc* pStbiData = stbi_load(filepath.data(), &m_Width, &m_Height, &m_Channels, requiredChannels);
		if (pStbiData != nullptr)
		{
			if (m_pData != nullptr)
				delete[] m_pData;
			m_pData = pStbiData;

			if (requiredChannels != 0)
				m_Channels = requiredChannels;
			m_Filepath = filepath;
			return true;
		}
		return false;
	}

	bool LocalTexture2D::WriteFile(std::string_view filepath)
	{
		return WriteFile(filepath, GetDefaultVerticalFlip());
	}

	bool LocalTexture2D::WriteFile(std::string_view filepath, bool flipVertically)
	{
		PROFILE_FUNCTION();

		stbi_flip_vertically_on_write(flipVertically);
		// TODO: let the user decide the output file format
		return m_pData != nullptr && stbi_write_png(filepath.data(), m_Width, m_Height, m_Channels, m_pData, 0) != 0;
	}

	bool LocalTexture2D::SetSubregion(const LocalTexture2D& crTexture, sint32 positionX, sint32 positionY)
	{
		PROFILE_FUNCTION();

		if (m_Channels == crTexture.m_Channels && positionX + crTexture.m_Width <= m_Width && positionX >= 0 && positionY + crTexture.m_Height <= m_Height && positionY >= 0)
		{
			size_t textureIncrement = static_cast<size_t>(crTexture.m_Width) * m_Channels;
			size_t increment = static_cast<size_t>(m_Width) * m_Channels;

			uint8* pSource = crTexture.m_pData;
			uint8* pDestination = m_pData + ((static_cast<size_t>(positionY) * m_Width + positionX) * m_Channels);
			for (sint32 y = 0; y < crTexture.m_Height; y++, pSource += textureIncrement, pDestination += increment)
				memcpy_s(pDestination, textureIncrement, pSource, textureIncrement);
			return true;
		}
		return false;
	}

	Ref<LocalTexture2D> LocalTexture2D::CreateRef()
	{ return eng::CreateRef<LocalTexture2D>(); }

	Ref<LocalTexture2D> LocalTexture2D::CreateRef(std::string_view filepath, sint32 requiredChannels)
	{ return eng::CreateRef<LocalTexture2D>(filepath, requiredChannels); }

	Ref<LocalTexture2D> LocalTexture2D::CreateRef(std::string_view filepath, bool flipVertically, sint32 requiredChannels)
	{ return eng::CreateRef<LocalTexture2D>(filepath, flipVertically, requiredChannels); }

	Ref<LocalTexture2D> LocalTexture2D::CreateRef(sint32 width, sint32 height, sint32 channels)
	{ return eng::CreateRef<LocalTexture2D>(width, height, channels); }
}
