#include "Engine/pch.h"
#include "Platform/RendererAPI/OpenGL/OpenGLRendererAPI.h"

namespace eng
{
	static constexpr GLenum UnconvertRendererPrimitive(RendererPrimitive primitive)
	{
		switch (primitive)
		{
			case RendererPrimitive_Points:                 return GL_POINTS;
			case RendererPrimitive_Lines:                  return GL_LINES;
			case RendererPrimitive_LineStrip:              return GL_LINE_STRIP;
			case RendererPrimitive_Triangles:              return GL_TRIANGLES;
			case RendererPrimitive_TriangleStrip:          return GL_TRIANGLE_STRIP;
			case RendererPrimitive_LinesAdjacency:         return GL_LINES_ADJACENCY;
			case RendererPrimitive_LineStripAdjacency:     return GL_LINE_STRIP_ADJACENCY;
			case RendererPrimitive_TrianglesAdjacency:     return GL_TRIANGLES_ADJACENCY;
			case RendererPrimitive_TriangleStripAdjacency: return GL_TRIANGLE_STRIP_ADJACENCY;
			case RendererPrimitive_LineLoop:               return GL_LINE_LOOP;
			case RendererPrimitive_TriangleFan:            return GL_TRIANGLE_FAN;
		}

		CORE_ASSERT(false, "Unknown Renderer Primitive!");
		return 0;
	}

	static constexpr GLenum UnconvertIndexBufferElementType(IndexBufferElementType type)
	{
		switch (type)
		{
			case IndexBufferElementType_UInt32:	return GL_UNSIGNED_INT;
			case IndexBufferElementType_UInt16:	return GL_UNSIGNED_SHORT;
			case IndexBufferElementType_UInt8:	return GL_UNSIGNED_BYTE;
		}

		CORE_ASSERT(false, "Unknown Index Buffer Element Type!");
		return 0;
	}

	static constexpr void DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* cpMessage, const void* cpUserParam)
	{
		UNUSED(source, type, id, length, cpUserParam);
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         LOG_CORE_FATAL(cpMessage); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       LOG_CORE_ERROR(cpMessage); return;
			case GL_DEBUG_SEVERITY_LOW:          LOG_CORE_WARN(cpMessage);  return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: LOG_CORE_TRACE(cpMessage); return;
		}

		CORE_ASSERT(false, "Unknown OpenGL severity level={0}.", severity);
	}

	OpenGLRendererAPI::OpenGLRendererAPI()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#if CONFIG_PROFILE || CONFIG_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(&DebugMessageCallback, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif
	}

	void OpenGLRendererAPI::EnableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		m_ClearBits |= GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
	}

	void OpenGLRendererAPI::DisableDepthTest()
	{
		glDisable(GL_DEPTH_TEST);
		glDepthFunc(GL_ALWAYS);
		m_ClearBits &= ~(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLRendererAPI::EnableBlending()
	{
		glEnable(GL_BLEND);
	}

	void OpenGLRendererAPI::DisableBlending()
	{
		glDisable(GL_BLEND);
	}

	void OpenGLRendererAPI::EnableCulling()
	{
		glEnable(GL_CULL_FACE);
	}

	void OpenGLRendererAPI::DisableCulling()
	{
		glDisable(GL_CULL_FACE);
	}

	void OpenGLRendererAPI::SetViewport(const glm::s32vec2& crPosition, const glm::s32vec2& crSize)
	{
		glViewport(crPosition.x, crPosition.y, crSize.x, crSize.y);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(m_ClearBits);
	}

	void OpenGLRendererAPI::ClearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& crColor)
	{
		glClearColor(crColor.r, crColor.g, crColor.b, crColor.a);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& crVertexArray, const Ref<IndexBuffer>& crIndexBuffer, uint32 offset, uint32 count, RendererPrimitive primitive)
	{
		crVertexArray->Bind();
		crIndexBuffer->Bind();

		GLenum glPrimitive = UnconvertRendererPrimitive(primitive);
		GLsizei indexCount = static_cast<GLsizei>(count != 0 ? count : crIndexBuffer->GetCount());
		GLenum glType = UnconvertIndexBufferElementType(crIndexBuffer->GetType());
		auto pOffset = (const void*)(offset * static_cast<GLsizeiptr>(GetIndexBufferElementSize(crIndexBuffer->GetType())));
		glDrawElements(glPrimitive, indexCount, glType, pOffset);
	}

	sint32 OpenGLRendererAPI::GetMaxTextureSlots()
	{
		GLint maxTextureSlots = 0;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureSlots);
		return static_cast<sint32>(maxTextureSlots);
	}

	sint32 OpenGLRendererAPI::GetMaxTextureSize()
	{
		GLint maxTextureSize = 0;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
		return static_cast<sint32>(maxTextureSize);
	}

	sint32 OpenGLRendererAPI::GetMaxTextureArrayLayers()
	{
		GLint maxTextureArrayLayers = 0;
		glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &maxTextureArrayLayers);
		return static_cast<sint32>(maxTextureArrayLayers);
	}

	sint32 OpenGLRendererAPI::GetMaxFramebufferWidth()
	{
		GLint maxFramebufferWidth = 0;
		glGetIntegerv(GL_MAX_FRAMEBUFFER_WIDTH, &maxFramebufferWidth);
		return static_cast<sint32>(maxFramebufferWidth);
	}

	sint32 OpenGLRendererAPI::GetMaxFramebufferHeight()
	{
		GLint maxFramebufferHeight = 0;
		glGetIntegerv(GL_MAX_FRAMEBUFFER_HEIGHT, &maxFramebufferHeight);
		return static_cast<sint32>(maxFramebufferHeight);
	}

	sint32 OpenGLRendererAPI::GetMaxFramebufferColorAttachments()
	{
		GLint maxFramebufferColorAttachments = 0;
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxFramebufferColorAttachments);
		return static_cast<sint32>(maxFramebufferColorAttachments);
	}
}
