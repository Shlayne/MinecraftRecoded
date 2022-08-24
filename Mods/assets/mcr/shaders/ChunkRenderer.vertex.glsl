#version 460 core

layout(location = 0) in uint packedVertex;

layout(location = 0) out uint Output_PackedVertex;

uniform mat4 viewProjection;
uniform vec3 cameraLocalPos;
uniform uint packedRenderChunkPos;

// Unpacks a 3 component vector in the form 0bZZZYYYXXX where there are N bits of each component.
uvec3 UnpackUnsigned(uint packedData, uint bits)
{
	uint mask = (1 << bits) - 1;
	return uvec3(packedData & mask, (packedData >> bits) & mask, (packedData >> (bits << 1)) & mask);
}

// Same thing as UnpackUnsigned except the N-1th bit (the sign bit) is copied to the upper bits.
ivec3 UnpackSigned(uint packedData, uint bits)
{
	uint mask = (1 << bits) - 1;
	uvec3 unpackedData = uvec3(packedData & mask, (packedData >> bits) & mask, (packedData >> (bits << 1)) & mask);
	return ivec3(((unpackedData >> (bits - 1)) * ~mask) | unpackedData);
}

vec3 GetPos(vec3 localPosition)
{
	return UnpackSigned(packedRenderChunkPos, 10) * 16 + (localPosition - cameraLocalPos);
}

void main(void)
{
	vec3 localPosition = UnpackUnsigned(packedVertex, 5);
	gl_Position = viewProjection * vec4(GetPos(localPosition), 1.0);
	Output_PackedVertex = packedVertex;
}
