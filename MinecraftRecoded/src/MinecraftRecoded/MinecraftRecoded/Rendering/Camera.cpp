#include "MinecraftRecoded/pch.h"
#include "Camera.h"

namespace mcr
{
	Camera::Camera(float fov, float zNear, float zFar) noexcept
		: m_FOV(fov), m_Near(zNear), m_Far(zFar) {}

	glm::mat4 Camera::GetViewProjection(const glm::vec3& rotation) const noexcept
	{
		return m_Projection * glm::inverse(glm::toMat4(glm::quat(rotation)));
	}

	void Camera::Resize(const glm::s32vec2& size) noexcept
	{
		ASSERT(size.x > 0 && size.y > 0, "Camera given invalid size.");

		float aspect = static_cast<float>(size.x) / size.y;
		m_Projection = glm::perspective(m_FOV, aspect, m_Near, m_Far);
	}
}
