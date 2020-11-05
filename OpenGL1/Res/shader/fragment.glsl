#version 410 core

out vec4 color;

in vec3 Normal;
in vec3 fragPos;

struct block_Material{
    vec3 ambientStrength;
    vec3 diffusionFactor;
    vec3 specularStrength;
    int shineExp;
};
uniform block_Material block;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;


void main()
{
    vec3 ambient = block.ambientStrength * lightColor;

    vec3 normDir = normalize(Normal);
    vec3 lightDir= normalize(lightPos- fragPos);
    float diffusionFactor = max(dot(lightDir,normDir),0.0);
    vec3 diffuseColor =  block.diffusionFactor * lightColor;

    vec3 viewDir=normalize(fragPos-viewPos);
    vec3 reflectDir = reflect(lightDir,normDir);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), pow(2,block.shineExp));
    vec3 specular = block.specularStrength * spec * lightColor;  

    vec3 result = (block.ambientStrength + diffuseColor +specular) * objectColor;
    color = vec4(result, 1.0);
};