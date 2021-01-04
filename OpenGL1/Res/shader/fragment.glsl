#version 410 core
#define NO_OF_PBLOCKS 4

out vec4 color;

in vec3 Normal;
in vec3 fragPos;
in vec2 texCoord;

struct block_Material{
    vec3 ambientStrength;
    vec3 diffusionFactor;
    vec3 specularStrength;
    float shineExp;
};
struct texture_Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shine;
};
struct FarLightBlock{
    vec3 amb;
    vec3 diffusionFactor;
    vec3 specularStrength;
    vec3 direction;
};
struct PointLightBlock{
    vec3 position;
    
    vec3 ambient;
    vec3 diffusionFactor;
    vec3 specularStrength;

    float constant;
    float lconstant;
    float qconstant;
};
struct SpotLightBlock{
    vec3 position;
    vec3 direction;
    float cutoffphi;
    float cutoffinner;
    float cutoffouter;

    vec3 amb;
    vec3 diffusionFactor;
    vec3 specularStrength;

    float constant;
    float lconstant;
    float qconstant;
};

uniform block_Material block;
uniform SpotLightBlock lblock;
uniform texture_Material tBlock;
uniform FarLightBlock fblock;
uniform PointLightBlock pblock[NO_OF_PBLOCKS];
uniform vec3 viewPos;

vec3 calcSpotLightBlock(SpotLightBlock lblock, vec3 Normal , vec3 viewDir){
    vec3 OutPut = vec3(0.0f);
    
    vec3 lightDir= normalize(lblock.position - fragPos);

    float theta = dot(lightDir, normalize(-lblock.direction));
    float epsilon = lblock.cutoffinner- (lblock.cutoffouter);
    float intensity =clamp((theta - (lblock.cutoffouter)/ epsilon ), 0.0 , 1.0);
    
  
    vec3 normDir = normalize(Normal);
    float dist = length(lblock.position - fragPos);
    float attenuation = 1.0 / (lblock.constant + lblock.lconstant * dist + lblock.qconstant * (dist *dist));

    vec3 ambient = vec3(texture(tBlock.diffuse, texCoord).rgb) * lblock.amb;
    float diff = max(dot(lightDir,normDir),0.0);
    vec3 diffuseColor =  lblock.diffusionFactor * (diff * vec3(texture(tBlock.diffuse, texCoord).rgb));

    vec3 reflectDir = reflect(lightDir,normDir);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), pow(2,tBlock.shine));
    vec3 specular = vec3(texture(tBlock.specular,texCoord)) * spec * lblock.specularStrength;  

    vec3 emission = texture(tBlock.emission, texCoord).rgb;

    diffuseColor  *= intensity;
    specular *= intensity;

    OutPut = (ambient + diffuseColor + specular)* attenuation  ;

    return OutPut;
}
vec3 calcFarLightBlock(FarLightBlock fblock , vec3 Normal ,vec3 viewDir){
    vec3 OutPut = vec3(0.0f);

    vec3 lightDir = normalize(fblock.direction);
    vec3 normDir = normalize (Normal);
    
    vec3 ambient =vec3 (texture(tBlock.diffuse, texCoord).rgb)* fblock.amb;
    float diff = max(dot(lightDir, normDir),0.0);
    vec3 diffuseColor =fblock.diffusionFactor * (diff * vec3 (texture (tBlock.diffuse , texCoord).rgb));

    vec3 reflectDir = reflect (lightDir, normDir);
    float spec = pow(max(dot(viewDir, reflectDir),0.0),pow(2,tBlock.shine));
    vec3 specular = vec3 (texture(tBlock.specular,texCoord))* spec* fblock.specularStrength;

    vec3 emission = texture(tBlock.emission, texCoord).rgb;
    
    OutPut = (ambient + diffuseColor + specular );
    return OutPut;
}
vec3 calcPointLight(PointLightBlock light, vec3 Normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(Normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), tBlock.shine);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.lconstant * distance + 
  			     light.qconstant * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(tBlock.diffuse, texCoord));
    vec3 diffuse  = light.diffusionFactor  * diff * vec3(texture(tBlock.diffuse, texCoord));
    vec3 specular = light.specularStrength * spec * vec3(texture(tBlock.specular, texCoord));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

void main()
{
    vec3 result = vec3(0.0f);

    vec3 viewDir = normalize (fragPos - viewPos) ;

    result += calcFarLightBlock(fblock , Normal , viewDir);

    //for (int i =0 ; i < NO_OF_PBLOCKS ; i++)
    //  result += calcPointLight(pblock[i], Normal ,fragPos , viewDir);

    result += calcSpotLightBlock(lblock, Normal ,viewDir);
    //result += calcSpotLightBlock();
    
    color = vec4(result, 1.0);

};