#version 460 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

layout(location = 0) in uint Input_PackedVertex[];

layout(location = 0) out vec3 Output_Normal;

const vec3 faceNormals[] = vec3[](
	vec3(0, 1, 0),
	vec3(0, 0, 1),
	vec3(1, 0, 0),
	vec3(0)
);

void main(void)
{
	for (uint i = 0; i < 3; i++)
	{
		Output_Normal = faceNormals[(Input_PackedVertex[i] >> 16) & 0x3];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
}
