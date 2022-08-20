#version 460 core

layout(location = 0) in vec3 Input_Normal;

layout(location = 0) out vec4 Output_Color;

void main(void)
{
	Output_Color = vec4(Input_Normal, 1.0);
}
