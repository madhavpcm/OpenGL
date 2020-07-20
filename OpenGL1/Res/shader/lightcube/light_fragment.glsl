#version 410 core
uniform float mixValue;
out vec4 color;

void main()
{
    color = vec4(1.0 ,1.0 , 1.0 , 1.0 +mixValue);
};