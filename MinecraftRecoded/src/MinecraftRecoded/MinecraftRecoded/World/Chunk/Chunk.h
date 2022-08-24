#pragma once

#include "World/Chunk/ChunkConstants.h"
#include "Block/BlockInstance.h"
#include "Rendering/ChunkMesh.h"
#include <vector>

namespace mcr
{
	class Chunk
	{
	public:
		Chunk();
		~Chunk();
	public:
		const ChunkMesh& GetMesh(RenderPass pass) const;
	private:
		void RegenerateMeshes();
	private:
		friend class World;
		friend class ChunkMeshGenerator;

		// These assume each component of localPos is in the range [0, s_ChunkBlockSize).

		static uint16 GetIndex(glm::s8vec3 localPos) noexcept;

		void SetBlock(uint16 index, BlockInstance&& block);
		BlockInstance& GetBlock(uint16 index);
		const BlockInstance& GetBlock(uint16 index) const;

		void SetBlock(glm::s8vec3 localPos, BlockInstance&& block);
		BlockInstance& GetBlock(glm::s8vec3 localPos);
		const BlockInstance& GetBlock(glm::s8vec3 localPos) const;
	private:
		BlockInstance* m_Blocks = nullptr;
		std::vector<ChunkMesh> m_Meshes;
	};
}
