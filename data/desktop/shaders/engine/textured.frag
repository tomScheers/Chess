#version 330 core

out vec4 o_color;
uniform sampler2D u_texture;

in vec2 v_tex_coord;

void main()
{
    vec4 tex_color = texture(u_texture, v_tex_coord);
    // o_color = vec4(1.0, 0.0, 0.0, 1.0);
    o_color = tex_color;
}