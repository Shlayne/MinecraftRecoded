#include "MinecraftRecoded/pch.h"
#include "BlockRenderer.h"
#include <Engine/Rendering/Renderer.h>
#include <Engine/Rendering/RendererCapabilities.h>
#include <Engine/Rendering/Shader.h>

namespace mcr
{
	struct Vertex
	{
		glm::vec3 position;
	};

	struct CameraBuffer
	{
		glm::mat4 viewProjection;
	};

	struct BlockRendererData
	{
		eng::Ref<eng::VertexArray> vertexArray;
		eng::Ref<eng::VertexBuffer> vertexBuffer;
		eng::Ref<eng::IndexBuffer> indexBuffer;
		eng::Ref<eng::UniformBuffer> cameraBuffer;
		eng::Ref<eng::Shader> shader;
	};
	static BlockRendererData* s_BlockRendererData = nullptr;

	void BlockRenderer::Init()
	{
		ASSERT(s_BlockRendererData == nullptr, "Tried to reinitialize block renderer.");
		s_BlockRendererData = new BlockRendererData();
		auto& data = *s_BlockRendererData;

		//LOG_INFO("Max Texture Size:         {}", eng::RendererCapabilities::GetMaxTextureSize());
		//LOG_INFO("Max Texture Slots:        {}", eng::RendererCapabilities::GetMaxTextureSlots());
		//LOG_INFO("Max Texture Array Layers: {}", eng::RendererCapabilities::GetMaxTextureArrayLayers());

		data.vertexBuffer = eng::VertexBuffer::CreateRef(sizeof(Vertex) * 4 * 6, nullptr, eng::BufferUsage_DynamicDraw);
		data.vertexBuffer->SetLayout({
			eng::VertexBufferElementType_Float3, // position
		});

		data.vertexArray = eng::VertexArray::CreateRef();
		data.vertexArray->AddVertexBuffer(data.vertexBuffer);

		constexpr uint32 indices[]
		{
			 0,  1,  2,  2,  3,  0,
			 4,  5,  6,  6,  7,  4,
			 8,  9, 10, 10, 11,  8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20
		};
		data.indexBuffer = eng::IndexBuffer::CreateRef(sizeof(indices) / sizeof(*indices), indices, eng::BufferUsage_StaticDraw, eng::IndexBufferElementType_UInt32);

		data.shader = eng::Shader::CreateRef({
			{ eng::ShaderStageType_Vertex, "Assets/mcr/shaders/BlockRenderer.vertex.glsl" },
			{ eng::ShaderStageType_Geometry, "Assets/mcr/shaders/BlockRenderer.geometry.glsl" },
			{ eng::ShaderStageType_Fragment, "Assets/mcr/shaders/BlockRenderer.fragment.glsl" },
		});

		data.cameraBuffer = eng::UniformBuffer::CreateRef(sizeof(CameraBuffer), 0, nullptr, eng::BufferUsage_DynamicDraw);
	}

	void BlockRenderer::Shutdown()
	{
		ASSERT(s_BlockRendererData != nullptr, "Tried to reshutdown block renderer.");
		auto& data = *s_BlockRendererData;

		eng::DestroyRef(data.vertexArray);
		eng::DestroyRef(data.vertexBuffer);
		eng::DestroyRef(data.indexBuffer);
		eng::DestroyRef(data.cameraBuffer);
		eng::DestroyRef(data.shader);

		delete s_BlockRendererData;
		s_BlockRendererData = nullptr;
	}

	void BlockRenderer::RenderBlock(const BlockPos& blockPos, const Camera& camera, const EntityPos& cameraPos, const glm::vec3& cameraRotation)
	{
		ASSERT(s_BlockRendererData != nullptr, "Tried to use block renderer before it was initialized.");
		auto& data = *s_BlockRendererData;

		constexpr glm::vec3 blockVertexPositions[]
		{
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(1.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		};

		constexpr uint32 blockFaceIndices[4 * 6]
		{
			0, 4, 6, 2, // Left
			5, 1, 3, 7, // Right
			0, 1, 5, 4, // Bottom
			6, 7, 3, 2, // Top
			1, 0, 2, 3, // Back
			4, 5, 7, 6  // Front
		};

		Vertex vertices[4 * 6]{};

		glm::s64vec3 renderChunkPos = blockPos.GetChunkPosition() - cameraPos.GetChunkPosition();
		glm::vec3 renderLocalPos = glm::vec3(blockPos.GetLocalPosition()) - cameraPos.GetLocalPosition();

#if ENABLE_ASSERTS
		glm::s64vec3 scaledChunkPos = renderChunkPos * static_cast<sint64>(s_ChunkBlockSize);
		CORE_ASSERT(glm::s64vec3(glm::vec3(scaledChunkPos)) == scaledChunkPos, "Block tried to render at an imprecise position.");
		glm::vec3 renderPos = scaledChunkPos + glm::s64vec3(renderLocalPos);
#else
		glm::vec3 renderPos = renderChunkPos * static_cast<sint64>(s_ChunkBlockSize) + glm::s64vec3(renderLocalPos);
#endif

		for (uint32 i = 0; i < 4 * 6; i++)
			vertices[i].position = blockVertexPositions[blockFaceIndices[i]] + renderPos;

		data.vertexBuffer->SetData(vertices, sizeof(vertices));
		glm::mat4 viewProjection = camera.GetViewProjection(cameraRotation);
		data.cameraBuffer->SetData(glm::value_ptr(viewProjection), sizeof(viewProjection));
		data.shader->Bind();

		eng::Renderer::EnableBlending();
		eng::Renderer::EnableCulling();
		eng::Renderer::EnableDepthTest();
		eng::Renderer::DrawIndexed(data.vertexArray, data.indexBuffer);
	}
}
