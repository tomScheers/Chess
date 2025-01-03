#version 330 core

layout(location = 0) in vec4 i_Position;
layout(location = 1) in vec2 i_TexCoord;

out vec2 v_TexCoord;

uniform float u_RotX;
uniform float u_RotY;
uniform mat4 u_MVP;

void main()
{
    mat4 rotationX = mat4(1.0);
    rotationX[1][1] = cos(u_RotX);
    rotationX[1][2] = -sin(u_RotX);
    rotationX[2][1] = sin(u_RotX);
    rotationX[2][2] = cos(u_RotX);

    // Rotation around Y-axis (Y-axis rotation matrix)
    mat4 rotationY = mat4(1.0);
    rotationY[0][0] = cos(u_RotY);
    rotationY[0][2] = sin(u_RotY);
    rotationY[2][0] = -sin(u_RotY);
    rotationY[2][2] = cos(u_RotY);

    mat4 rotationMatrix = rotationY * rotationX;
    vec4 rotatedPosition = rotationMatrix * i_Position;

    gl_Position = u_MVP * rotatedPosition;
    v_TexCoord = i_TexCoord;
}