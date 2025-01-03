#version 330 core

layout(location = 0) in vec4 i_Position;
layout(location = 1) in vec2 i_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * i_Position;
    v_TexCoord = i_TexCoord;
}