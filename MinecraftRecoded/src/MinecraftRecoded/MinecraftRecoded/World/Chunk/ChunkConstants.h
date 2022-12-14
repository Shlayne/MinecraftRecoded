#pragma once

#include <Engine/Core/Int.h>

namespace mcr
{
	static constexpr sint64 s_ChunkBlockSize = 16ll; // Size of chunk, in blocks, in each axis.
	static constexpr sint64 s_TotalBlocksInChunk = s_ChunkBlockSize * s_ChunkBlockSize * s_ChunkBlockSize;
}
