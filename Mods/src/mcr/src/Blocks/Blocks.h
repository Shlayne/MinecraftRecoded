#pragma once

#include "World/Chunk/Block/Block.h"

namespace mcr
{
	class AirBlock : public Block
	{
	public:
		static constexpr std::string_view ID = "air";
	public:
		constexpr virtual std::string_view GetID() const noexcept override { return ID; }
		constexpr virtual bool RendersInPass(Face face, RenderPass pass) const noexcept override { return false; }
	};

	class StoneBlock : public Block
	{
	public:
		static constexpr std::string_view ID = "stone";
	public:
		constexpr virtual std::string_view GetID() const noexcept override { return ID; }
		constexpr virtual bool RendersInPass(Face face, RenderPass pass) const noexcept override { return pass == RenderPass_Opaque; }
	};
}
