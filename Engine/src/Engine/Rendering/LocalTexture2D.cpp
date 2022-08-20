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
		m_Data = new uint8[size]{ 0 };
	}

	LocalTexture2D::LocalTexture2D(const LocalTexture2D& texture)
		: m_Filepath(texture.m_Filepath), m_Width(texture.m_Width), m_Height(texture.m_Height), m_Channels(texture.m_Channels)
	{
		if (texture)
		{
			size_t size = static_cast<size_t>(m_Width) * m_Height * m_Channels;
			m_Data = new uint8[size];
			memcpy_s(m_Data, size, texture.m_Data, size);
		}
		else
			m_Data = nullptr;
	}

	LocalTexture2D::LocalTexture2D(LocalTexture2D&& texture) noexcept
		: m_Filepath(std::move(texture.m_Filepath)), m_Width(texture.m_Width), m_Height(texture.m_Height), m_Channels(texture.m_Channels), m_Data(texture.m_Data)
	{
		texture.m_Width = 0;
		texture.m_Height = 0;
		texture.m_Channels = 0;
		texture.m_Data = nullptr;
	}

	LocalTexture2D& LocalTexture2D::operator=(const LocalTexture2D& texture)
	{
		if (this != &texture)
		{
			if (m_Data != nullptr)
				delete[] m_Data;

			m_Width = texture.m_Width;
			m_Height = texture.m_Height;
			m_Channels = texture.m_Channels;
			m_Filepath = texture.m_Filepath;

			if (texture)
			{
				size_t size = static_cast<size_t>(m_Width) * m_Height * m_Channels;
				m_Data = new uint8[size];
				memcpy_s(m_Data, size, texture.m_Data, size);
			}
			else
				m_Data = nullptr;
		}
		return *this;
	}

	LocalTexture2D& LocalTexture2D::operator=(LocalTexture2D&& texture) noexcept
	{
		if (this != &texture)
		{
			m_Filepath = std::move(texture.m_Filepath);
			m_Width = texture.m_Width;
			m_Height = texture.m_Height;
			m_Channels = texture.m_Channels;
			m_Data = texture.m_Data;

			texture.m_Width = 0;
			texture.m_Height = 0;
			texture.m_Channels = 0;
			texture.m_Data = nullptr;
		}
		return *this;
	}

	LocalTexture2D::~LocalTexture2D()
	{
		delete[] m_Data;
	}

	bool LocalTexture2D::ReadFile(std::string_view filepath, sint32 requiredChannels)
	{
		return ReadFile(filepath, GetDefaultVerticalFlip(), requiredChannels);
	}

	bool LocalTexture2D::ReadFile(std::string_view filepath, bool flipVertically, sint32 requiredChannels)
	{
		PROFILE_FUNCTION();

		stbi_set_flip_vertically_on_load(flipVertically);
		stbi_uc* stbiData = stbi_load(filepath.data(), &m_Width, &m_Height, &m_Channels, requiredChannels);
		if (stbiData != nullptr)
		{
			if (m_Data != nullptr)
				delete[] m_Data;
			m_Data = stbiData;

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
		return m_Data != nullptr && stbi_write_png(filepath.data(), m_Width, m_Height, m_Channels, m_Data, 0) != 0;
	}

	bool LocalTexture2D::SetSubregion(const LocalTexture2D& texture, sint32 positionX, sint32 positionY)
	{
		PROFILE_FUNCTION();

		if (m_Channels == texture.m_Channels && positionX + texture.m_Width <= m_Width && positionX >= 0 && positionY + texture.m_Height <= m_Height && positionY >= 0)
		{
			size_t textureIncrement = static_cast<size_t>(texture.m_Width) * m_Channels;
			size_t increment = static_cast<size_t>(m_Width) * m_Channels;

			uint8* source = texture.m_Data;
			uint8* destination = m_Data + ((static_cast<size_t>(positionY) * m_Width + positionX) * m_Channels);
			for (sint32 y = 0; y < texture.m_Height; y++, source += textureIncrement, destination += increment)
				memcpy_s(destination, textureIncrement, source, textureIncrement);
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
