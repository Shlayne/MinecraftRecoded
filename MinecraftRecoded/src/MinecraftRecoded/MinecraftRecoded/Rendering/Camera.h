#pragma once

#include <glm/glm.hpp>

namespace mcr
{
	class Camera
	{
	public:
		Camera(float fov = glm::radians(90.0f), float zNear = 0.001f, float zFar = 1000.0f) noexcept;
	public:
		glm::mat4 GetViewProjection(const glm::vec3& rotation) const noexcept;
		void Resize(const glm::s32vec2& size) noexcept;
	private:
		float m_FOV;
		float m_Near;
		float m_Far;
		glm::mat4 m_Projection{ 1.0f };
	};
}
