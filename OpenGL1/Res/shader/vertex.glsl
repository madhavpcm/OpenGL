#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 atexCoord;

out vec3 Normal;
out vec3 fragPos;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection*view*model*position ;
    fragPos = vec3(model * position);
    texCoord = atexCoord;
    Normal = mat3(transpose(inverse(model)))* aNormal;
};