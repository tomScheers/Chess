#version 330 core

in vec2 v_TexCoord;

out vec4 o_Color;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    o_Color = texColor;
    if(texColor.a < 0.1)
        discard;
}