#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textCoords;

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform vec4 color;

void main()
{
    TexCoords = textCoords;
    ParticleColor = color;
    gl_Position = projection * view * model * vec4(position,1.0);
}