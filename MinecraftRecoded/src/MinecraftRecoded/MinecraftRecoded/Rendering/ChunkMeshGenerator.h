#pragma once

#include "World/Chunk/Chunk.h"
#include "ChunkMesh.h"
#include "RenderPass.h"

namespace mcr
{
	class ChunkMeshGenerator
	{
	public:
		static void GenerateMesh(const Chunk& chunk, ChunkMesh& outMesh, RenderPass pass);
	private:
		ChunkMeshGenerator() = delete;
		ChunkMeshGenerator(const ChunkMeshGenerator&) = delete;
		ChunkMeshGenerator(ChunkMeshGenerator&&) = delete;
		ChunkMeshGenerator& operator=(const ChunkMeshGenerator&) = delete;
		ChunkMeshGenerator& operator=(ChunkMeshGenerator&&) = delete;
		~ChunkMeshGenerator() = delete;
	};
}
