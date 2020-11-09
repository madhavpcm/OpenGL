#include "blockMaterials.h"
#include<json/json.h>
#include<iostream>
#include<stdint.h>
#include<fstream>

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
const void block_Materials::printData()
{
	std::cout << blockName << std::endl;
}
const void block_Materials::setBlockName(std::string a) {
	blockName = a;
}
block_Materials::block_Materials() :
	blockName("default"),
	ambientStrength(glm::vec3(0.1f)),
	diffusionFactor(glm::vec3(0.3f)),
	specularStrength(glm::vec3(0.4f)),
	shinynessExponent(5)
{
	
}
using namespace Json;
void readJsonFileStatic(std::vector<block_Materials> &database) {
	Json::Value root;
	std::ifstream data;
	Json::CharReaderBuilder builder;
	JSONCPP_STRING errs;

	data.open("Res/BlockData/blockData.json");
	builder["collectComments"] = true;

	if (!parseFromStream(builder, data, &root, &errs)) {
		std::cout << errs << std::endl;
		return;
	}

	auto members = root.getMemberNames();
	std::vector<float> parser[25];
	uint16_t i = 0;
	auto blocks = root.getMemberNames();
	for (auto& block : blocks) {
		glm::vec3 ambient_temp, diffuse_temp, specular_temp;
		auto blockData = root.get(block, 0);
		auto BlockDataNames = blockData.getMemberNames();
		for (auto& name : BlockDataNames) {
			float temp = stof((std::string)blockData.get(name, -1).asString());
			parser[i].push_back(temp);
		}
		float shinyness_temp;
		ambient_temp =  glm::vec3(parser[i][0], parser[i][1] ,parser[i][2]);
		diffuse_temp =  glm::vec3(parser[i][3], parser[i][4], parser[i][5]);
		specular_temp = glm::vec3(parser[i][6], parser[i][7], parser[i][8]);
		shinyness_temp = parser[i][9];
		database[i].setBlockName(block);
		database[i].setAmbientStrength(ambient_temp);
		database[i].setDiffusionFactor(diffuse_temp);
		database[i].setSpecularStrength(specular_temp);
		database[i].setShinynessExponent(shinyness_temp);
		i++;

		}
}