#pragma once

#include "World/Chunk/Chunk.h"
#include "World/Chunk/Block/BlockPos.h"
#include "World/Entity/EntityPos.h"
#include "Camera.h"

namespace mcr
{
	class ChunkRenderer
	{
	public:
		static void Init();
		static void Shutdown();
	public:
		static void RenderChunk(const Chunk& chunk, const glm::s64vec3& chunkPos, const Camera& camera, const EntityPos& cameraPos, const glm::vec3& cameraRotation);
	private:
		ChunkRenderer() = delete;
		ChunkRenderer(const ChunkRenderer&) = delete;
		ChunkRenderer(ChunkRenderer&&) = delete;
		ChunkRenderer& operator=(const ChunkRenderer&) = delete;
		ChunkRenderer& operator=(ChunkRenderer&&) = delete;
		~ChunkRenderer() = delete;
	};
}
