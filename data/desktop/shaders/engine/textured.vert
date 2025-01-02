#version 330 core

layout(location = 0) in vec4 i_position;
layout(location = 1) in vec2 i_tex_coord;

uniform mat4 u_MVP;

out vec2 v_tex_coord;

void main()
{
    gl_Position = u_MVP * i_position;
    v_tex_coord = i_tex_coord;
}