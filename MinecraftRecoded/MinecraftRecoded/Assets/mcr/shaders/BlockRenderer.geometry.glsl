#version 460 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

layout(location = 0) out vec3 Output_Normal;

void main(void)
{
	vec3 position0 = gl_in[0].gl_Position.xyz;
	vec3 position1 = gl_in[1].gl_Position.xyz;
	vec3 position2 = gl_in[2].gl_Position.xyz;
	vec3 normal = abs(normalize(cross(position0 - position1, position0 - position2)));

	for (uint i = 0; i < 3; i++)
	{
		Output_Normal = normal;
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
}
