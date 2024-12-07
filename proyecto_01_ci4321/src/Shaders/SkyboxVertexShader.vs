#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    TexCoords = aPos;
    vec4 WVP_Pos = projection * view * model * vec4(aPos, 1.0);
    gl_Position = WVP_Pos.xyww;
}  