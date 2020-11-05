#include "blockMaterials.h"

const void block_Materials::setAmbientStrength(glm::vec3 a) {
	ambientStrength = a;
}
const void block_Materials::setDiffusionFactor(glm::vec3 a) {
	diffusionFactor = a;
}
const void block_Materials::setSpecularStrength(glm::vec3 a) {
	specularStrength = a;
}
const void block_Materials::setShinynessExponent(int a) {
	shinynessExponent = a;
}
block_Materials::block_Materials() :
	ambientStrength(glm::vec3(0.1f)),
	diffusionFactor(glm::vec3(0.3f)),
	specularStrength(glm::vec3(0.4f)),
	shinynessExponent(5)
{
	
}