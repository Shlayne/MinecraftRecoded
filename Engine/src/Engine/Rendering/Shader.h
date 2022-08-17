#pragma once

#include "Engine/Core/Core.h"
#include <glm/glm.hpp>
#include <string_view>

namespace eng
{
	using ShaderStageType = uint8;
	enum : ShaderStageType
	{
		ShaderStageType_Vertex,
		ShaderStageType_TessolationControl,
		ShaderStageType_TessolationEvaluation,
		ShaderStageType_Geometry,
		ShaderStageType_Fragment,
		ShaderStageType_Compute
	};

	struct ShaderStage
	{
		ShaderStageType type;
		std::string_view filepath;
	};

	class Shader
	{
	public:
		static Ref<Shader> Create(std::initializer_list<ShaderStage> stages);
		virtual ~Shader() = default;
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetFloat (std::string_view name, float              value) = 0;
		virtual void SetFloat2(std::string_view name, const glm::vec2&   value) = 0;
		virtual void SetFloat3(std::string_view name, const glm::vec3&   value) = 0;
		virtual void SetFloat4(std::string_view name, const glm::vec4&   value) = 0;
		virtual void SetInt   (std::string_view name, sint32             value) = 0;
		virtual void SetInt2  (std::string_view name, const glm::ivec2&  value) = 0;
		virtual void SetInt3  (std::string_view name, const glm::ivec3&  value) = 0;
		virtual void SetInt4  (std::string_view name, const glm::ivec4&  value) = 0;
		virtual void SetUInt  (std::string_view name, uint32             value) = 0;
		virtual void SetUInt2 (std::string_view name, const glm::uvec2&  value) = 0;
		virtual void SetUInt3 (std::string_view name, const glm::uvec3&  value) = 0;
		virtual void SetUInt4 (std::string_view name, const glm::uvec4&  value) = 0;
		virtual void SetBool  (std::string_view name, bool               value) = 0;
		virtual void SetBool2 (std::string_view name, const glm::bvec2&  value) = 0;
		virtual void SetBool3 (std::string_view name, const glm::bvec3&  value) = 0;
		virtual void SetBool4 (std::string_view name, const glm::bvec4&  value) = 0;
		virtual void SetMat2  (std::string_view name, const glm::mat2&   value) = 0;
		virtual void SetMat2x3(std::string_view name, const glm::mat2x3& value) = 0;
		virtual void SetMat2x4(std::string_view name, const glm::mat2x4& value) = 0;
		virtual void SetMat3x2(std::string_view name, const glm::mat3x2& value) = 0;
		virtual void SetMat3  (std::string_view name, const glm::mat3&   value) = 0;
		virtual void SetMat3x4(std::string_view name, const glm::mat3x4& value) = 0;
		virtual void SetMat4x2(std::string_view name, const glm::mat4x2& value) = 0;
		virtual void SetMat4x3(std::string_view name, const glm::mat4x3& value) = 0;
		virtual void SetMat4  (std::string_view name, const glm::mat4&   value) = 0;
		virtual void SetInts  (std::string_view name, const sint32*      values, sint32 count) = 0;
		virtual void SetUInts (std::string_view name, const uint32*      values, sint32 count) = 0;
	};
}
