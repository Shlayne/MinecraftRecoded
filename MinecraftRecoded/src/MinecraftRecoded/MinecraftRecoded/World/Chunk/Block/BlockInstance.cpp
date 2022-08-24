#include "MinecraftRecoded/pch.h"
#include "BlockInstance.h"

namespace mcr
{
	BlockInstance::BlockInstance(const Block* block) noexcept
		: m_Block(block) {}

	const Block* BlockInstance::GetBlock() const noexcept
	{
		return m_Block;
	}

	void BlockInstance::SetBlock(const Block* block) noexcept
	{
		m_Block = block;
	}
}
