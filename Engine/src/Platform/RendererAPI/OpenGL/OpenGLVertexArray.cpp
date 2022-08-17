#include "Engine/pch.h"
#include "Platform/RendererAPI/OpenGL/OpenGLVertexArray.h"

namespace eng
{
	static constexpr GLenum UnconvertVertexBufferElementType(VertexBufferElementType type)
	{
		switch (type)
		{
			case VertexBufferElementType_Float:
			case VertexBufferElementType_Float2:
			case VertexBufferElementType_Float3:
			case VertexBufferElementType_Float4:
				return GL_FLOAT;
			case VertexBufferElementType_Int:
			case VertexBufferElementType_Int2:
			case VertexBufferElementType_Int3:
			case VertexBufferElementType_Int4:
				return GL_INT;
			case VertexBufferElementType_UInt:
			case VertexBufferElementType_UInt2:
			case VertexBufferElementType_UInt3:
			case VertexBufferElementType_UInt4:
				return GL_UNSIGNED_INT;
		}

		CORE_ASSERT(false, "Unknown Vetex Buffer Element Type!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		CORE_ASSERT(vertexBuffer != nullptr, "Vertex buffer is nullptr!");
		CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size() != 0, "Vertex buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
	
		const VertexBufferLayout& crLayout = vertexBuffer->GetLayout();
		for (const VertexBufferElement& crElement : crLayout)
		{
			GLenum elementType = UnconvertVertexBufferElementType(crElement.type);

			switch (crElement.type)
			{
				case VertexBufferElementType_Float:
				case VertexBufferElementType_Float2:
				case VertexBufferElementType_Float3:
				case VertexBufferElementType_Float4:
					glEnableVertexAttribArray(m_VertexAttributeIndex);
					glVertexAttribPointer(m_VertexAttributeIndex, crElement.count, elementType, crElement.normalized ? GL_TRUE : GL_FALSE, crLayout.GetStride(), (const void*)crElement.offset);
					m_VertexAttributeIndex++;
					break;
				case VertexBufferElementType_Int:
				case VertexBufferElementType_Int2:
				case VertexBufferElementType_Int3:
				case VertexBufferElementType_Int4:
				case VertexBufferElementType_UInt:
				case VertexBufferElementType_UInt2:
				case VertexBufferElementType_UInt3:
				case VertexBufferElementType_UInt4:
					glEnableVertexAttribArray(m_VertexAttributeIndex);
					glVertexAttribIPointer(m_VertexAttributeIndex, crElement.count, elementType, crLayout.GetStride(), (const void*)crElement.offset);
					m_VertexAttributeIndex++;
					break;
			}
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}
}
