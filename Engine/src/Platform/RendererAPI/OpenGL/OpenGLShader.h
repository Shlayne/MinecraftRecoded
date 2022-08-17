#pragma once

#include "Engine/Rendering/Shader.h"
#include <glad/glad.h>
#include <unordered_map>

namespace eng
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(std::initializer_list<ShaderStage> stages);
		virtual ~OpenGLShader();
	public:
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetFloat (std::string_view name, float              value) override;
		virtual void SetFloat2(std::string_view name, const glm::vec2&   value) override;
		virtual void SetFloat3(std::string_view name, const glm::vec3&   value) override;
		virtual void SetFloat4(std::string_view name, const glm::vec4&   value) override;
		virtual void SetInt   (std::string_view name, sint32             value) override;
		virtual void SetInt2  (std::string_view name, const glm::ivec2&  value) override;
		virtual void SetInt3  (std::string_view name, const glm::ivec3&  value) override;
		virtual void SetInt4  (std::string_view name, const glm::ivec4&  value) override;
		virtual void SetUInt  (std::string_view name, uint32             value) override;
		virtual void SetUInt2 (std::string_view name, const glm::uvec2&  value) override;
		virtual void SetUInt3 (std::string_view name, const glm::uvec3&  value) override;
		virtual void SetUInt4 (std::string_view name, const glm::uvec4&  value) override;
		virtual void SetBool  (std::string_view name, bool               value) override;
		virtual void SetBool2 (std::string_view name, const glm::bvec2&  value) override;
		virtual void SetBool3 (std::string_view name, const glm::bvec3&  value) override;
		virtual void SetBool4 (std::string_view name, const glm::bvec4&  value) override;
		virtual void SetMat2  (std::string_view name, const glm::mat2&   value) override;
		virtual void SetMat2x3(std::string_view name, const glm::mat2x3& value) override;
		virtual void SetMat2x4(std::string_view name, const glm::mat2x4& value) override;
		virtual void SetMat3x2(std::string_view name, const glm::mat3x2& value) override;
		virtual void SetMat3  (std::string_view name, const glm::mat3&   value) override;
		virtual void SetMat3x4(std::string_view name, const glm::mat3x4& value) override;
		virtual void SetMat4x2(std::string_view name, const glm::mat4x2& value) override;
		virtual void SetMat4x3(std::string_view name, const glm::mat4x3& value) override;
		virtual void SetMat4  (std::string_view name, const glm::mat4&   value) override;
		virtual void SetInts  (std::string_view name, const sint32*      values, sint32 count) override;
		virtual void SetUInts (std::string_view name, const uint32*      values, sint32 count) override;
	private:
		GLint GetUniformLocation(std::string_view name);
	private:
		GLuint m_RendererID = 0;
		std::unordered_map<std::string_view, GLint> m_UniformLocations;
	};
}
