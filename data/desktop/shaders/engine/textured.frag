#version 330 core

in vec2 v_tex_coord;

uniform sampler2D u_texture;

out vec4 o_color;

void main()
{
    vec4 tex_color = texture(u_texture, v_tex_coord);
    o_color = tex_color;
}