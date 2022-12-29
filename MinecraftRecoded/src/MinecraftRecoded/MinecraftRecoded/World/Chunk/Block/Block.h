#pragma once

#include "World/Chunk/Block/Face.h"
#include "Rendering/RenderPass.h"
#include "Modding/Registerable.h"
#include <string>
#include <vector>

// todo: dont use classes and polymorphism to define blocks
// that is highly inefficient, and explains why actual minecraft is slow now
// use a buffer of data inside the block class to define its properties, not a bunch of functions.
// that should also be a lot more cache friendly, since all block types can be allocated contigously.
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
