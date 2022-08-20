#include "Engine/pch.h"
#include "Engine/Rendering/Buffer.h"
#include "Engine/Rendering/RendererAPI.h"
#include "Platform/RendererAPI/OpenGL/OpenGLBuffer.h"

namespace eng
{
	Ref<VertexBuffer> VertexBuffer::CreateRef(uint32 size, const void* data, BufferUsage usage)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return eng::CreateRef<OpenGLVertexBuffer>(size, data, usage);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}

	Ref<IndexBuffer> IndexBuffer::CreateRef(uint32 count, const void* data, BufferUsage usage, IndexBufferElementType type)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return eng::CreateRef<OpenGLIndexBuffer>(count, data, usage, type);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}

	Ref<UniformBuffer> UniformBuffer::CreateRef(uint32 size, uint32 binding, const void* data, BufferUsage usage)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return eng::CreateRef<OpenGLUniformBuffer>(size, binding, data, usage);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}
}
