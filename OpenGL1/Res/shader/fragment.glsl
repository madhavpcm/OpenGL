#version 410 core

out vec4 color;

in vec3 Normal;
in vec3 fragPos;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 normDir = normalize(Normal);
    vec3 lightDir= normalize(lightPos- fragPos);
    float diffusionFactor = max(dot(lightDir,normDir),0.0);
    vec3 diffuseColor = diffusionFactor * lightColor;

    vec3 result = (ambientStrength + diffuseColor) * objectColor;
    color = vec4(result, 1.0);
};