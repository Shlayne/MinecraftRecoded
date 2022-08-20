#include "Engine/pch.h"
#include "Platform/RendererAPI/OpenGL/OpenGLBuffer.h"

namespace eng
{
	static constexpr GLenum UnconvertBufferUsage(BufferUsage usage)
	{
		switch (usage)
		{
			case BufferUsage_StreamDraw:  return GL_STREAM_DRAW;
			case BufferUsage_StreamRead:  return GL_STREAM_READ;
			case BufferUsage_StreamCopy:  return GL_STREAM_COPY;
			case BufferUsage_StaticDraw:  return GL_STATIC_DRAW;
			case BufferUsage_StaticRead:  return GL_STATIC_READ;
			case BufferUsage_StaticCopy:  return GL_STATIC_COPY;
			case BufferUsage_DynamicDraw: return GL_DYNAMIC_DRAW;
			case BufferUsage_DynamicRead: return GL_DYNAMIC_READ;
			case BufferUsage_DynamicCopy: return GL_DYNAMIC_COPY;
		}

		CORE_ASSERT(false, "Unknown Buffer Usage!");
		return 0;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32 size, const void* data, BufferUsage usage)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, UnconvertBufferUsage(usage));
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32 size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32 count, const void* data, BufferUsage usage, IndexBufferElementType type)
		: m_Count(count), m_Type(type)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * static_cast<GLsizeiptr>(GetIndexBufferElementSize(type)), data, UnconvertBufferUsage(usage));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::SetData(const void* data, uint32 count)
	{
		CORE_ASSERT(count <= m_Count, "Index buffer count out of bounds!");

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * static_cast<GLsizeiptr>(GetIndexBufferElementSize(m_Type)), data);
	}

	OpenGLUniformBuffer::OpenGLUniformBuffer(uint32 size, uint32 binding, const void* data, BufferUsage usage)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, data, UnconvertBufferUsage(usage));
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLUniformBuffer::SetData(const void* data, uint32 size, uint32 offset)
	{
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}
}
