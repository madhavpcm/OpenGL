#version 410 core

layout(location = 0) out vec4 color;
in vec2 v_texCoord;
uniform float mixValue;
uniform vec4 u_color;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main()
{
    vec4 texColor = mix(texture(u_Texture1,v_texCoord), texture(u_Texture2,v_texCoord),mixValue);
    color = texColor;
};