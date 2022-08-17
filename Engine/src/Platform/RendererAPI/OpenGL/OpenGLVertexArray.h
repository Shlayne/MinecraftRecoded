#pragma once

#include "Engine/Rendering/VertexArray.h"
#include <glad/glad.h>

namespace eng
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
	public:
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		inline virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
	private:
		GLuint m_RendererID = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		uint32_t m_VertexAttributeIndex = 0;
	};
}
