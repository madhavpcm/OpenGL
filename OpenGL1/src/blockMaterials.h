#pragma once
#include<glm/glm.hpp>
#include<dist/json/json.h>

class block_Materials
{
private:
	glm::vec3 ambientStrength;
	glm::vec3 diffusionFactor;
	glm::vec3 specularStrength;
	int shinynessExponent;
public:
	block_Materials();

	const glm::vec3 getAmbientStrength()  { return ambientStrength; }
	const glm::vec3 getDiffusionFactor()  { return diffusionFactor; }
	const glm::vec3 getSpecularStrength() { return specularStrength; }
	const int getshinynessExponent()	  { return shinynessExponent; }

	const void setAmbientStrength(glm::vec3 a);
	const void setDiffusionFactor(glm::vec3 a);
	const void setSpecularStrength(glm::vec3 a);
	const void setShinynessExponent(int a);
	const void set
	/*block_Materials& operator = (block_Materials& obj) {
		block_Materials temp;
		temp.ambientStrength = obj.ambientStrength;
		temp.specularStrength = obj.specularStrength;
		temp.diffusionFactor = obj.diffusionFactor;
		temp.shinynessExponent = obj.shinynessExponent;
		return temp;
	}*/

};



