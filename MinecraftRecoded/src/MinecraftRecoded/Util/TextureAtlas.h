#pragma once

#include "Engine/Rendering/LocalTexture2D.h"
#include <glm/glm.hpp>

namespace eng
{
	class TextureAtlas
	{
	public:
		TextureAtlas();
		~TextureAtlas();
	public:
		// Returns the texture coordinates, in unnormalized texture coordinate space,
		// of the texture in the atlas. These coordinates are for the texture returned
		// by Create(). After you have added all of your textures, before you even call
		// Create(), you can get normalized texture coordinates by dividing this return
		// value by GetTextureSize(). Don't forget to cast to a float!
		// Also, add textures from largest to smallest for the best packing results.
		// If the texture can't be added to the atlas (because the atlas wouldn't fit on the GPU),
		// then glm::s32vec2(-1) is returned.
		glm::s32vec2 AddTexture(const Ref<LocalTexture2D>& texture);

		// Returns a texture that has the smallest possible size that contains
		// every texture provided through AddTexture. The returned textures will
		// have an aspect ratio of 1, and their size will be constrained to
		// powers of 2, e.g.: 1x1, 2x2, 4x4... 256x256, 512x512, 1024x1024...
		Ref<LocalTexture2D> Create();

		constexpr const glm::s32vec2& GetTextureSize() const noexcept { return m_CurrentTextureSize; }
	private:
		struct TextureNode
		{
			constexpr TextureNode(const glm::s32vec2& position, const glm::s32vec2& size) noexcept
				: position(position), size(size) {}

			Ref<LocalTexture2D> texture = nullptr;

			// These are in unnormalized texture coordinate space.
			glm::s32vec2 position;
			glm::s32vec2 size;

			TextureNode* left = nullptr;
			TextureNode* right = nullptr;
		};

		TextureNode* AddTexture(TextureNode* node, const Ref<LocalTexture2D>& texture, const glm::s32vec2& size);
		void PutTexture(TextureNode* node, const Ref<LocalTexture2D>& atlasTexture);
		void Clear(TextureNode* node);

		glm::s32vec2 m_MaxTextureSize;
		TextureNode* m_Root;
		glm::s32vec2 m_CurrentTextureSize{ 1 };
	private:
		TextureAtlas(const TextureAtlas&) = delete;
		TextureAtlas(TextureAtlas&&) = delete;
		TextureAtlas& operator=(const TextureAtlas&) = delete;
		TextureAtlas& operator=(TextureAtlas&&) = delete;
	};
}
