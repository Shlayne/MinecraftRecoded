#pragma once

#include "Engine/Rendering/Buffer.h"
#include <glad/glad.h>

namespace eng
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32 size, const void* cpData, BufferUsage usage);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* cpData, uint32 size) override;

		virtual const VertexBufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const VertexBufferLayout& crLayout) override { m_Layout = crLayout; }
	private:
		GLuint m_RendererID = 0;
		VertexBufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32 count, const void* cpData, BufferUsage usage, IndexBufferElementType type);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* cpData, uint32 count) override;

		virtual uint32 GetCount() const override { return m_Count; }
		virtual IndexBufferElementType GetType() const override { return m_Type; }
	private:
		GLuint m_RendererID = 0;
		uint32 m_Count = 0;
		IndexBufferElementType m_Type;
	};

	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(uint32 size, uint32 binding, const void* cpData, BufferUsage usage);
		virtual ~OpenGLUniformBuffer();

		virtual void SetData(const void* cpData, uint32 size, uint32 offset = 0) override;
	private:
		GLuint m_RendererID = 0;
	};
}
