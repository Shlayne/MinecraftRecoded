#pragma once

#include "World/Chunk/Block/Face.h"
#include "Rendering/RenderPass.h"
#include "Modding/Registerable.h"
#include <string>

namespace mcr
{
	class Block : public Registerable
	{
	public:
		constexpr virtual ~Block() noexcept = default;
	public:
		constexpr virtual bool RendersInPass(Face face, RenderPass pass) const noexcept = 0;
	};
}
