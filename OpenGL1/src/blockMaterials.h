#pragma once
#include<glm/glm.hpp>
#include<vector>
#include<string>
class block_Materials
{
private:
	std::string blockName;
	glm::vec3 ambientStrength;
	glm::vec3 diffusionFactor;
	glm::vec3 specularStrength;
	int shinynessExponent;
public:
	block_Materials();
	const std::string getBlockName()		  { return blockName; }
	const glm::vec3 getAmbientStrength()  { return ambientStrength; }
	const glm::vec3 getDiffusionFactor()  { return diffusionFactor; }
	const glm::vec3 getSpecularStrength() { return specularStrength; }
	const int getshinynessExponent()	  { return shinynessExponent; }
	const void printData();

	const void setBlockName(std::string a);
	const void setAmbientStrength(glm::vec3 a);
	const void setDiffusionFactor(glm::vec3 a);
	const void setSpecularStrength(glm::vec3 a);
	const void setShinynessExponent(int a);

};
void readJsonFileStatic(std::vector<block_Materials>& database);



