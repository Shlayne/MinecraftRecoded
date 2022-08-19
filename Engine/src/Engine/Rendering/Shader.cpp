#include "Engine/pch.h"
#include "Engine/Rendering/Shader.h"
#include "Engine/Rendering/RendererAPI.h"
#include "Platform/RendererAPI/OpenGL/OpenGLShader.h"

namespace eng
{
	Ref<Shader> Shader::CreateRef(std::initializer_list<ShaderStage> stages)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API_OpenGL: return eng::CreateRef<OpenGLShader>(stages);
			UNKNOWN_RENDERER_API(RendererAPI::GetAPI(), nullptr);
		}
	}
}
