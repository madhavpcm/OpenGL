#version 410 core

out vec4 color;

in vec3 Normal;
in vec3 fragPos;

uniform float ambientStrength;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform float specularStrength;
uniform float shineExp;

void main()
{
    vec3 ambient = ambientStrength * lightColor;

    vec3 normDir = normalize(Normal);
    vec3 lightDir= normalize(lightPos- fragPos);
    float diffusionFactor = max(dot(lightDir,normDir),0.0);
    vec3 diffuseColor = diffusionFactor * lightColor;

    vec3 viewDir=normalize(fragPos-viewPos);
    vec3 reflectDir = reflect(lightDir,normDir);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), pow(2,shineExp));
    vec3 specular = specularStrength * spec * lightColor;  

    vec3 result = (ambientStrength + diffuseColor +specular) * objectColor;
    color = vec4(result, 1.0);
};