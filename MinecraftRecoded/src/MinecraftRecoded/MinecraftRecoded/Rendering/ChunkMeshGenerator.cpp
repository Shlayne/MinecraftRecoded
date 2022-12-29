#include "MinecraftRecoded/pch.h"
#include "ChunkMeshGenerator.h"

namespace mcr
{
	void ChunkMeshGenerator::GenerateMesh(const Chunk& chunk, ChunkMesh& outMesh, RenderPass pass)
	{
		for (sint8 z = 0; z < s_ChunkBlockSize; z++)
		{
			for (sint8 y = 0; y < s_ChunkBlockSize; y++)
			{
				for (sint8 x = 0; x < s_ChunkBlockSize; x++)
				{
					const BlockInstance* blockInstance = chunk.GetBlock({ x, y, z });
					if (blockInstance != nullptr)
					{
						const Block* block = blockInstance->GetBlock();
						for (Face face = Face_First; face != Face_Count; (*(Face_*)&face)++)
						{
							if (block->RendersInPass(face, pass))
							{
								const BlockInstance* blockInstanceOnFace = chunk.GetBlockOnFace({ x, y, z }, face);
								if (blockInstanceOnFace == nullptr || !blockInstanceOnFace->GetBlock()->RendersInPass(OppositeFace(face), RenderPass_Opaque))
								{
									auto indexOffset = static_cast<ChunkMesh::Index>(outMesh.vertices.size());

									constexpr ChunkMesh::Index faceIndices[]
									{
										0, 1, 5, 4, // Bottom
										6, 7, 3, 2, // Top
										1, 0, 2, 3, // North
										4, 5, 7, 6, // South
										0, 4, 6, 2, // West
										5, 1, 3, 7, // East
									};

									ChunkMesh::Vertex vertex;
									vertex.faceIndex = face;
									for (uint8 v = 0; v < 4; v++)
									{
										ChunkMesh::Index index = faceIndices[face * 4 + v];
										vertex.localPosX = x + ((index & 0b001) >> 0);
										vertex.localPosY = y + ((index & 0b010) >> 1);
										vertex.localPosZ = z + ((index & 0b100) >> 2);
										outMesh.vertices.push_back(vertex);
									}

									//outMesh.indices.insert(outMesh.indices.end(),
									//{
									//	static_cast<ChunkMesh::Index>(indexOffset + 0),
									//	static_cast<ChunkMesh::Index>(indexOffset + 1),
									//	static_cast<ChunkMesh::Index>(indexOffset + 2),
									//	static_cast<ChunkMesh::Index>(indexOffset + 2),
									//	static_cast<ChunkMesh::Index>(indexOffset + 3),
									//	static_cast<ChunkMesh::Index>(indexOffset + 0),
									//});
								}
							}
						}
					}
				}
			}
		}
	}
}
