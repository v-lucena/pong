#version 460

layout (location = 0) in vec2 vertex; // vertex(vec2 position)

uniform mat4 model;
uniform mat4 projection;

void main()
{
	glPosition = projection * model * vec4(vertex, 0.0, 1.0)
}