#include "MinecraftRecoded/pch.h"
#include "Chunk.h"
#include "Modding/Registry.h"
#include "Rendering/ChunkMeshGenerator.h"

namespace mcr
{
	Chunk::Chunk()
	{
		// TODO: if chunk is completely full of air, don't allocate m_Blocks.
		// Same for storing chunk to disk.
		m_Blocks = new BlockInstance[s_TotalBlocksInChunk];

		// TODO: move world gen
		std::fill_n(m_Blocks, s_TotalBlocksInChunk, BlockInstance(Registry::GetBlock("mcr:stone")));
		//const Block* stone = Registry::GetBlock("mcr:stone");
		//for (sint32 z = 0; z < s_ChunkBlockSize; z++)
		//	for (sint32 y = 0; y < s_ChunkBlockSize; y++)
		//		for (sint32 x = 0; x < s_ChunkBlockSize; x++)
		//			m_Blocks[GetIndex({ x, y, z })].SetBlock(stone);

		RegenerateMeshes();
	}

	Chunk::~Chunk()
	{
		delete[] m_Blocks;
	}

	const ChunkMesh& Chunk::GetMesh(RenderPass pass) const
	{
		ASSERT(pass < RenderPass_Count, "Tried to get invalid mesh from chunk for render pass = {}.", +pass);
		return m_Meshes[pass];
	}

	void Chunk::RegenerateMeshes()
	{
		m_Meshes.clear();
		m_Meshes.reserve(RenderPass_Count);
		for (RenderPass pass = RenderPass_First; pass < RenderPass_Count; (*(RenderPass_*)&pass)++)
			ChunkMeshGenerator::GenerateMesh(*this, m_Meshes.emplace_back(), pass);
	}

	uint16 Chunk::GetIndex(glm::s8vec3 localPos) noexcept
	{
		ASSERT(
			0 <= localPos.x && localPos.x < s_ChunkBlockSize &&
			0 <= localPos.y && localPos.y < s_ChunkBlockSize &&
			0 <= localPos.z && localPos.z < s_ChunkBlockSize,
			"Block index out of bounds for local pos = <{},{},{}>",
			localPos.x, localPos.y, localPos.z
		);

		return localPos.z << 8 | localPos.x << 4 | localPos.y;
	}

	void Chunk::SetBlock(uint16 index, BlockInstance&& block)
	{
		m_Blocks[index] = std::move(block);
	}

	BlockInstance& Chunk::GetBlock(uint16 index)
	{
		return m_Blocks[index];
	}

	const BlockInstance& Chunk::GetBlock(uint16 index) const
	{
		return m_Blocks[index];
	}

	void Chunk::SetBlock(glm::s8vec3 localPos, BlockInstance&& block)
	{
		return SetBlock(GetIndex(localPos), std::move(block));
	}

	BlockInstance& Chunk::GetBlock(glm::s8vec3 localPos)
	{
		return GetBlock(GetIndex(localPos));
	}

	const BlockInstance& Chunk::GetBlock(glm::s8vec3 localPos) const
	{
		return GetBlock(GetIndex(localPos));
	}
}
