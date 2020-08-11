#version 410 core

layout(location = 0) in vec4 position;
layout(location = 2) in vec3 aNormal;

out vec3 Normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection*view*model*position ;
    fragPos = vec3(model * position);
    Normal = aNormal;
};