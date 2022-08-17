#include "Engine/pch.h"
#include "Platform/RendererAPI/OpenGL/OpenGLShader.h"
#include "Engine/IO/FileIO.h"

namespace eng
{
	static constexpr GLenum UnconvertShaderStageType(ShaderStageType type)
	{
		switch (type)
		{
			case ShaderStageType_Vertex:                return GL_VERTEX_SHADER;
			case ShaderStageType_TessolationControl:    return GL_TESS_CONTROL_SHADER;
			case ShaderStageType_TessolationEvaluation: return GL_TESS_EVALUATION_SHADER;
			case ShaderStageType_Geometry:              return GL_GEOMETRY_SHADER;
			case ShaderStageType_Fragment:              return GL_FRAGMENT_SHADER;
			case ShaderStageType_Compute:               return GL_COMPUTE_SHADER;
		}

		CORE_ASSERT(false, "Unknown Shader Stage Type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(std::initializer_list<ShaderStage> stages)
	{
		PROFILE_FUNCTION();

		bool success = true;

		m_RendererID = glCreateProgram();

		std::vector<GLuint> shaderIDs;
		for (const auto& crStage : stages)
		{
			std::string file = io::ReadFile(crStage.filepath);
			if (file.empty())
			{
				LOG_CORE_WARN("Shader file=\"{0}\" does not exist or is empty.");
				success = false;
				break;
			}

			GLint length = static_cast<GLint>(file.size());
			if (length < 0)
			{
				LOG_CORE_WARN("Shader file=\"{0}\" so big it overflowed a 32-bit signed int... how in the???");
				success = false;
				break;
			}

			GLuint shaderID = shaderIDs.emplace_back(glCreateShader(UnconvertShaderStageType(crStage.type)));
			glShaderSource(shaderID, 1, reinterpret_cast<const GLchar* const*>(file.data()), &length);

			// Attach before compiling to not have to check when detaching shaders from the program.
			glAttachShader(m_RendererID, shaderID);

			// Compile shader
			glCompileShader(shaderID);
			GLint compiled;
			glGetProgramiv(shaderID, GL_COMPILE_STATUS, &compiled);
			if (compiled == GL_FALSE)
			{
				GLint length;
				glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &length);
				std::vector<GLchar> message(length);
				glGetProgramInfoLog(shaderID, length, &length, message.data());
				LOG_CORE_WARN("{0}", static_cast<char*>(message.data()));
				success = false;
				break;
			}
		}

		if (success)
		{
			// Link program
			glLinkProgram(m_RendererID);
			GLint linked;
			glGetProgramiv(m_RendererID, GL_LINK_STATUS, &linked);
			if (linked == GL_FALSE)
			{
				GLint length;
				glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &length);
				std::vector<GLchar> message(length);
				glGetProgramInfoLog(m_RendererID, length, &length, message.data());
				LOG_CORE_WARN("{0}", static_cast<char*>(message.data()));
				success = false;
			}

			if (success)
			{
				// Validate program
				glValidateProgram(m_RendererID);
				GLint validated;
				glGetProgramiv(m_RendererID, GL_VALIDATE_STATUS, &validated);
				if (validated == GL_FALSE)
				{
					GLint length;
					glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &length);
					std::vector<GLchar> message(length);
					glGetProgramInfoLog(m_RendererID, length, &length, message.data());
					LOG_CORE_WARN("{0}", static_cast<char*>(message.data()));
					success = false;
				}
			}
		}

		// Do this regardles of success
		for (auto shaderID : shaderIDs)
		{
			glDetachShader(m_RendererID, shaderID);
			glDeleteShader(shaderID);
		}

		if (!success)
		{
			LOG_CORE_WARN("Failed to create shader.");
			glDeleteProgram(m_RendererID);
			m_RendererID = 0;
		}
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	GLint OpenGLShader::GetUniformLocation(std::string_view name)
	{
		auto it = m_UniformLocations.find(name);
		if (it != m_UniformLocations.end())
			return it->second;

		GLint location = glGetUniformLocation(m_RendererID, name.data());
#if ENABLE_LOGGING
		if (location == -1)
			LOG_CORE_WARN("Unused shader uniform: {0}", name);
#endif
		m_UniformLocations[name] = location;
		return location;
	}

	void OpenGLShader::SetFloat(std::string_view name, float value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform1f(location, value);
	}

	void OpenGLShader::SetFloat2(std::string_view name, const glm::vec2& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform2fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetFloat3(std::string_view name, const glm::vec3& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform3fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetFloat4(std::string_view name, const glm::vec4& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform4fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetInt(std::string_view name, sint32 value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform1i(location, value);
	}

	void OpenGLShader::SetInt2(std::string_view name, const glm::ivec2& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform2iv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetInt3(std::string_view name, const glm::ivec3& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform3iv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetInt4(std::string_view name, const glm::ivec4& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform4iv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetUInt(std::string_view name, uint32 value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform1ui(location, value);
	}

	void OpenGLShader::SetUInt2(std::string_view name, const glm::uvec2& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform2uiv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetUInt3(std::string_view name, const glm::uvec3& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform3uiv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetUInt4(std::string_view name, const glm::uvec4& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform4uiv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetBool(std::string_view name, bool value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform1i(location, (int)value);
	}

	void OpenGLShader::SetBool2(std::string_view name, const glm::bvec2& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform2i(location, static_cast<GLint>(value.x), static_cast<GLint>(value.y));
	}

	void OpenGLShader::SetBool3(std::string_view name, const glm::bvec3& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform3i(location, static_cast<GLint>(value.x), static_cast<GLint>(value.y), static_cast<GLint>(value.z));
	}

	void OpenGLShader::SetBool4(std::string_view name, const glm::bvec4& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform4i(location, static_cast<GLint>(value.x), static_cast<GLint>(value.y), static_cast<GLint>(value.z), static_cast<GLint>(value.w));
	}

	void OpenGLShader::SetMat2(std::string_view name, const glm::mat2& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat2x3(std::string_view name, const glm::mat2x3& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniformMatrix2x3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat2x4(std::string_view name, const glm::mat2x4& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniformMatrix2x4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat3x2(std::string_view name, const glm::mat3x2& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniformMatrix3x2fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat3(std::string_view name, const glm::mat3& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat3x4(std::string_view name, const glm::mat3x4& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniformMatrix3x4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat4x2(std::string_view name, const glm::mat4x2& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniformMatrix4x2fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat4x3(std::string_view name, const glm::mat4x3& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniformMatrix4x3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat4(std::string_view name, const glm::mat4& value)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetInts(std::string_view name, const sint32* values, sint32 count)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform1iv(location, count, values);
	}

	void OpenGLShader::SetUInts(std::string_view name, const uint32* values, sint32 count)
	{
		GLint location = GetUniformLocation(name);
		if (location != -1) glUniform1uiv(location, count, values);
	}
}
