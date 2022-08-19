#pragma once

#include "World/Chunk/Block/BlockPos.h"
#include "World/Entity/EntityPos.h"
#include "Camera.h"

namespace mcr
{
	class BlockRenderer
	{
	public:
		static void Init();
		static void Shutdown();
	public:
		static void RenderBlock(const BlockPos& blockPos, const Camera& camera, const EntityPos& cameraPos, const glm::vec3& cameraRotation);
	private:
		BlockRenderer() = delete;
		BlockRenderer(const BlockRenderer&) = delete;
		BlockRenderer(BlockRenderer&&) = delete;
		BlockRenderer& operator=(const BlockRenderer&) = delete;
		BlockRenderer& operator=(BlockRenderer&&) = delete;
		~BlockRenderer() = delete;
	};
}
