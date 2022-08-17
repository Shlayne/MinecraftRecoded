#include "Engine/pch.h"
#include "Engine/Rendering/Buffer.h"
#include "Engine/Rendering/RendererAPI.h"
#include "Platform/RendererAPI/OpenGL/OpenGLBuffer.h"

namespace eng
{
	Ref<VertexBuffer> VertexBuffer::CreateRef(uint32 size, const void* cpData, BufferUsage usage)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return eng::CreateRef<OpenGLVertexBuffer>(size, cpData, usage);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}

	Ref<IndexBuffer> IndexBuffer::CreateRef(uint32 count, const void* cpData, BufferUsage usage, IndexBufferElementType type)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return eng::CreateRef<OpenGLIndexBuffer>(count, cpData, usage, type);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}

	Ref<UniformBuffer> UniformBuffer::CreateRef(uint32 size, uint32 binding, const void* cpData, BufferUsage usage)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return eng::CreateRef<OpenGLUniformBuffer>(size, binding, cpData, usage);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}
}
