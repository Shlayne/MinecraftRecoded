#pragma once

#include "Block.h"

namespace mcr
{
	class BlockInstance
	{
	public:
		BlockInstance() noexcept = default;
		BlockInstance(const Block* block) noexcept;
	public:
		const Block* GetBlock() const noexcept;
		void SetBlock(const Block* block) noexcept;
	private:
		const Block* m_Block = nullptr;
	};
}
