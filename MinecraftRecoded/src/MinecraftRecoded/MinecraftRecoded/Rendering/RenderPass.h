#pragma once

#include <Engine/Core/Int.h>

namespace mcr
{
	using RenderPass_ = uint8;
	enum RenderPass : RenderPass_
	{
		// Only alpha = 1.0f
		RenderPass_Opaque,

		// Only alpha = 0.0f or 1.0f
		RenderPass_Transparent,

		// Only alpha = 0.0f -> 1.0f
		RenderPass_Translucent,
	};
}
