#pragma once

#include <Engine/Core/Int.h>
#include <vector>

namespace mcr
{
	struct ChunkMesh
	{
		// Packed to optimize vram usage with negligible speed cost.
		struct Vertex
		{
			// position x, 5 bits, sum = 5 bits
			// position y, 5 bits, sum = 10 bits
			// position z, 5 bits, sum = 15 bits
			// face index, 3 bits, sum = 18 bits
			union
			{
				uint32 data = 0;
				struct
				{
					uint32 localPosX : 5;
					uint32 localPosY : 5;
					uint32 localPosZ : 5;
					uint32 faceIndex : 3;
				};
			};

			// 10-bit signed chunk position allows for blocks to be rendered at 16*2^(10-1) = 8192 blocks away from the camera.
			// The max bedrock render distance is 64 chunks (7-bit signed) = 16*2^(7-1) = 1024 blocks away.

			// uniform buffer:
			// view projection, 512 bits, sum = 512 bits
			// camera local position, 96 bits, sum = 608
			// chunk pos x, 10 bits, sum = 618 bits
			// chunk pos y, 10 bits, sum = 628 bits
			// chunk pos z, 10 bits, sum = 638 bits
			// total bits + padding = 80 bytes (I think)
		};

		using Index = uint32; // uint16

		std::vector<Vertex> vertices;
		//std::vector<Index> indices;
	};
}
