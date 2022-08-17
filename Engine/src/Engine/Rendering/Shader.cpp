#include "Engine/pch.h"
#include "Engine/Rendering/Shader.h"
#include "Engine/Rendering/RendererAPI.h"
#include "Platform/RendererAPI/OpenGL/OpenGLShader.h"

namespace eng
{
	Ref<Shader> Shader::Create(std::initializer_list<ShaderStage> stages)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return CreateRef<OpenGLShader>(stages);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}
}
