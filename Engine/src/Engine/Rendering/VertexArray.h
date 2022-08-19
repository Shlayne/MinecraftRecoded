#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Rendering/Buffer.h"

namespace eng
{
	class VertexArray
	{
	public:
		static Ref<VertexArray> CreateRef();
		virtual ~VertexArray() = default;
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
	};
}
