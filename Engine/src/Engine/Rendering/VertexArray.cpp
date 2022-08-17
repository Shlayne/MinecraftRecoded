#include "Engine/pch.h"
#include "Engine/Rendering/RendererAPI.h"
#include "Engine/Rendering/VertexArray.h"
#include "Platform/RendererAPI/OpenGL/OpenGLVertexArray.h"

namespace eng
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return CreateRef<OpenGLVertexArray>();
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}
}
