#version 330 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 color;

out vec4 v_Color;

uniform mat4 u_MVP;

void main()
{
	v_Color = color;

	gl_Position = u_MVP * pos;
}