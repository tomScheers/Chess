#version 330 core

layout(location = 0) in vec2 i_position;
layout(location = 1) in vec2 i_tex_coord;

out vec2 v_tex_coord;

void main()
{
    gl_Position = vec4(i_position, 0.0, 1.0);
    v_tex_coord = i_tex_coord;
}