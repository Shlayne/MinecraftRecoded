#include "MinecraftRecoded/pch.h"
#include "ChunkRenderer.h"
#include <Engine/Rendering/Renderer.h>
#include <Engine/Rendering/RendererCapabilities.h>
#include <Engine/Rendering/Shader.h>

namespace mcr
{
	static constexpr uint32 PackSigned(glm::s32vec3 unpackedData, uint8 bits)
	{
		unpackedData &= (1 << bits) - 1;
		return unpackedData.z << (bits << 1) | unpackedData.y << bits | unpackedData.x;
	}

	struct ChunkRendererData
	{
		eng::Ref<eng::VertexArray> vertexArray;
		eng::Ref<eng::VertexBuffer> vertexBuffer;
		eng::Ref<eng::IndexBuffer> indexBuffer;
		eng::Ref<eng::UniformBuffer> cameraBuffer;
		eng::Ref<eng::Shader> shader;
	};

	static ChunkRendererData* s_ChunkRendererData = nullptr;

	void ChunkRenderer::Init()
	{
		PROFILE_FUNCTION();

		ASSERT(s_ChunkRendererData == nullptr, "Tried to reinitialize chunk renderer.");
		s_ChunkRendererData = new ChunkRendererData();
		auto& data = *s_ChunkRendererData;

		constexpr size_t maxFaceCount = 6 * (s_ChunkBlockSize) * (s_ChunkBlockSize) * (s_ChunkBlockSize); // s_ChunkBlockSize / 2
		data.vertexBuffer = eng::VertexBuffer::CreateRef(sizeof(ChunkMesh::Vertex) * 4 * maxFaceCount, nullptr, eng::BufferUsage_DynamicDraw);
		data.vertexBuffer->SetLayout({
			eng::VertexBufferElementType_UInt
		});

		data.vertexArray = eng::VertexArray::CreateRef();
		data.vertexArray->AddVertexBuffer(data.vertexBuffer);

		constexpr uint32 maxIndexCount = 6 * maxFaceCount;
		ChunkMesh::Index* indices = new ChunkMesh::Index[maxIndexCount];
		for (ChunkMesh::Index index = 0, offset = 0; index < maxIndexCount; index += 6, offset += 4)
		{
			indices[index + 0] = offset + 0;
			indices[index + 1] = offset + 1;
			indices[index + 2] = offset + 2;
			indices[index + 3] = offset + 2;
			indices[index + 4] = offset + 3;
			indices[index + 5] = offset + 0;
		}
		data.indexBuffer = eng::IndexBuffer::CreateRef(maxIndexCount, indices, eng::BufferUsage_StaticDraw, eng::IndexBufferElementType_UInt32); // IndexBufferElementType_UInt16
		delete[] indices;

		data.shader = eng::Shader::CreateRef({
			{ eng::ShaderStageType_Vertex, "Assets/mcr/shaders/ChunkRenderer.vertex.glsl" },
			{ eng::ShaderStageType_Geometry, "Assets/mcr/shaders/ChunkRenderer.geometry.glsl" },
			{ eng::ShaderStageType_Fragment, "Assets/mcr/shaders/ChunkRenderer.fragment.glsl" },
		});
	}

	void ChunkRenderer::Shutdown()
	{
		PROFILE_FUNCTION();

		ASSERT(s_ChunkRendererData != nullptr, "Tried to reshutdown chunk renderer.");
		auto& data = *s_ChunkRendererData;

		eng::DestroyRef(data.vertexArray);
		eng::DestroyRef(data.vertexBuffer);
		eng::DestroyRef(data.indexBuffer);
		eng::DestroyRef(data.shader);

		delete s_ChunkRendererData;
		s_ChunkRendererData = nullptr;
	}

	void ChunkRenderer::RenderChunk(const Chunk& chunk, const glm::s64vec3& chunkPos, const Camera& camera, const EntityPos& cameraPos, const glm::vec3& cameraRotation)
	{
		PROFILE_FUNCTION();

		auto& data = *s_ChunkRendererData;

		glm::s64vec3 renderChunkPos = chunkPos - cameraPos.GetChunkPosition();
#if ENABLE_ASSERTS
		glm::s64vec3 absRenderChunkPos = glm::abs(renderChunkPos);
		ASSERT(
			absRenderChunkPos == (absRenderChunkPos & ((1ll << 10) - 1)),
			"Chunk tried to render at invalid render chunk position = <{},{},{}>",
			absRenderChunkPos.x, absRenderChunkPos.y, absRenderChunkPos.z
		);
#endif

		data.shader->Bind();
		data.shader->SetMat4("viewProjection", camera.GetViewProjection(cameraRotation));
		data.shader->SetFloat3("cameraLocalPos", cameraPos.GetLocalPosition());
		data.shader->SetUInt("packedRenderChunkPos", PackSigned(renderChunkPos, 10));

		{
			PROFILE_SCOPE("ChunkRenderer -> RenderPass_Opaque");

			auto& vertices = chunk.GetMesh(RenderPass_Opaque).vertices;
			uint32 size = static_cast<uint32>(vertices.size()) * sizeof(ChunkMesh::Vertex);
			data.vertexBuffer->SetData(vertices.data(), size);

			eng::Renderer::DisableBlending();
			eng::Renderer::EnableCulling();
			eng::Renderer::EnableDepthTest();
			eng::Renderer::DrawIndexed(data.vertexArray, data.indexBuffer);
		}

		{
			PROFILE_SCOPE("ChunkRenderer -> RenderPass_Transparent");

			auto& vertices = chunk.GetMesh(RenderPass_Transparent).vertices;
			uint32 size = static_cast<uint32>(vertices.size()) * sizeof(ChunkMesh::Vertex);
			if (size > 0)
			{
				data.vertexBuffer->SetData(vertices.data(), size);

				eng::Renderer::DisableBlending();
				eng::Renderer::EnableCulling();
				eng::Renderer::EnableDepthTest();
				eng::Renderer::DrawIndexed(data.vertexArray, data.indexBuffer);
			}
		}

		{
			PROFILE_SCOPE("ChunkRenderer -> RenderPass_Translucent");

			auto& vertices = chunk.GetMesh(RenderPass_Translucent).vertices;
			uint32 size = static_cast<uint32>(vertices.size()) * sizeof(ChunkMesh::Vertex);
			if (size > 0)
			{
				data.vertexBuffer->SetData(vertices.data(), size);

				eng::Renderer::EnableBlending();
				eng::Renderer::EnableCulling();
				eng::Renderer::EnableDepthTest();
				eng::Renderer::DrawIndexed(data.vertexArray, data.indexBuffer);
			}
		}

		data.shader->Unbind();
	}
}
