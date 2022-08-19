#version 460 core

layout(location = 0) in vec3 position;

layout(std140, binding = 0) uniform Camera
{
	mat4 viewProjection;
};

void main(void)
{
	gl_Position = viewProjection * vec4(position, 1.0);
}
