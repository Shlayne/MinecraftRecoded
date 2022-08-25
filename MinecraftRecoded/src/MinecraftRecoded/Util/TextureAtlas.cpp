#include "Engine/pch.h"
#include "TextureAtlas.h"
#include "Engine/Rendering/RendererCapabilities.h"

namespace eng
{
	TextureAtlas::TextureAtlas()
		: m_MaxTextureSize(RendererCapabilities::GetMaxTextureSize()), m_Root(new TextureNode(glm::s32vec2(0), m_MaxTextureSize)) {}

	TextureAtlas::~TextureAtlas()
	{
		Clear(m_Root);
	}

	glm::s32vec2 TextureAtlas::AddTexture(const Ref<LocalTexture2D>& texture)
	{
		PROFILE_FUNCTION();

		glm::s32vec2 textureSize = texture->GetSize();

		while ((textureSize.x < m_CurrentTextureSize.x && textureSize.y < m_CurrentTextureSize.y) || m_CurrentTextureSize.x < m_MaxTextureSize.x)
		{
			TextureNode* node = AddTexture(m_Root, texture, textureSize);
			if (node != nullptr)
				return node->position;
			else
				m_CurrentTextureSize <<= 1; // Keep the texture size a power of 2.
		}

		// If this happens, the atlas can't expand because it wouldn't fit on the GPU.
		return glm::s32vec2(-1);
	}

	// From: https://straypixels.net/texture-packing-for-fonts/
	TextureAtlas::TextureNode* TextureAtlas::AddTexture(TextureNode* node, const Ref<LocalTexture2D>& texture, const glm::s32vec2& size)
	{
		// If the node has a texture, it can only be a leaf node, so don't bother.
		if (node->texture != nullptr)
			return nullptr;
		// If the node has both children, search them for an opening.
		else if (node->left != nullptr && node->right != nullptr)
		{
			TextureNode* newLeftNode = AddTexture(node->left, texture, size);
			return newLeftNode != nullptr ? newLeftNode : AddTexture(node->right, texture, size);
		}
		// If an opening has been found.
		else
		{
			// Get the real size of the opening.
			glm::s32vec2 realSize(node->size);
			if (node->position.x + node->size.x == m_MaxTextureSize.x)
				realSize.x = m_CurrentTextureSize.x - node->position.x;
			if (node->position.y + node->size.y == m_MaxTextureSize.y)
				realSize.y = m_CurrentTextureSize.y - node->position.y;

			// If the size of the opening (which may technically be the max texture size) is the same size as the texture.
			if (node->size == size)
			{
				node->texture = texture;
				return node;
			}
			// If the opening is not big enough.
			else if (realSize.x < size.x || realSize.y < size.y)
				return nullptr;
			// If the texture fits in the opening.
			else
			{
				glm::s32vec2 remainingSize = realSize - size;
				bool splitVertically = remainingSize.x < remainingSize.y;

				// If the opening is the same size as the texture.
				if (remainingSize.x == 0 && remainingSize.y == 0)
					splitVertically = node->size.x <= node->size.y;

				// Get the right position and size of the opening and empty space.
				if (splitVertically)
				{
					node->left = new TextureNode(node->position, { node->size.x, size.y });
					node->right = new TextureNode({ node->position.x, node->position.y + size.y }, { node->size.x, node->size.y - size.y });
				}
				else
				{
					node->left = new TextureNode(node->position, { size.x, node->size.y });
					node->right = new TextureNode({ node->position.x + size.x, node->position.y }, { node->size.x - size.x, node->size.y });
				}

				return AddTexture(node->left, texture, size);
			}
		}
	}

	Ref<LocalTexture2D> TextureAtlas::Create()
	{
		PROFILE_FUNCTION();

		Ref<LocalTexture2D> atlasTexture = LocalTexture2D::CreateRef(m_CurrentTextureSize.x, m_CurrentTextureSize.y, 4);
		PutTexture(m_Root, atlasTexture);
		return atlasTexture;
	}

	void TextureAtlas::PutTexture(TextureNode* node, const Ref<LocalTexture2D>& atlasTexture)
	{
		if (node != nullptr)
		{
			if (node->texture != nullptr)
				atlasTexture->SetSubregion(*node->texture, node->position.x, node->position.y);
			// Since a node with a texture has no children, don't try to copy their
			// non-existent textures, because they themselves don't exist.
			else
			{
				PutTexture(node->left, atlasTexture);
				PutTexture(node->right, atlasTexture);
			}
		}
	}

	void TextureAtlas::Clear(TextureNode* node)
	{
		if (node)
		{
			Clear(node->left);
			Clear(node->right);
			delete node;
		}
	}
}
