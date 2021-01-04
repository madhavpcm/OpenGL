#include "blockMaterials.h"
#include<json/json.h>
#include<iostream>
#include<stdint.h>
#include<fstream>
using namespace Json;

GlobalBlock::GlobalBlock() :
	m_AmbientStrength(glm::vec3(0.21f,0.1f , 0.2f)),
	m_DiffusionFactor(glm::vec3(0.3f)),
	m_SpecularStrength(glm::vec3(0.4f))
{
	
}
const void GlobalBlock::SetAmbientStrength(glm::vec3 a) {
	m_AmbientStrength = a;
}
const void GlobalBlock::SetDiffusionFactor(glm::vec3 a) {
	m_DiffusionFactor = a;
}
const void GlobalBlock::SetSpecularStrength(glm::vec3 a) {
	m_SpecularStrength = a;
}
MaterialBlock::MaterialBlock() 
	:m_ShinynessExponent(6.0),m_BlockName("NONAME")
{}
const void MaterialBlock::SetShinynessExponent(std::uint32_t a) {
	m_ShinynessExponent = a;
}
const void MaterialBlock::SetBlockName(std::string a)
{
	m_BlockName = a;
}

FarLightBlock::FarLightBlock() :
	m_Direction(glm::vec3(3.0f, 4.0f, 2.0f))

{
}
const void FarLightBlock::SetDirection(glm::vec3 a)
{
	m_Direction = a;
}

void readJsonFileStatic(std::vector<MaterialBlock> &database) {
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
		database[i].SetBlockName(block);
		database[i].SetAmbientStrength(ambient_temp);
		database[i].SetDiffusionFactor(diffuse_temp);
		database[i].SetSpecularStrength(specular_temp);
		database[i].SetShinynessExponent(shinyness_temp);
		i++;

		}
}

PointLightBlock::PointLightBlock()
	:m_Position(glm::vec3(1.0f , 2.0f ,3.0f))
{
}
const void PointLightBlock::SetPosition(glm::vec3 a)
{
	m_Position = a;
}

SpotLightBlock::SpotLightBlock() 
	:m_CutoffPhi(glm::cos(glm::radians(12.5f))),m_SpotDirection(glm::vec3(1.0f, 1.0f ,1.0f)),
	m_CutoffInner(glm::cos(25.0f)),m_CutoffOuter(glm::cos(35.0f))
{
}
const void SpotLightBlock::SetCutoffPhi(float a) {
	m_CutoffPhi = a;
}
const void SpotLightBlock::SetCutoffInner(float a)
{
	m_CutoffInner = a;
}
const void SpotLightBlock::SetCutoffOuter(float a)
{
	m_CutoffOuter = a;
}
const void SpotLightBlock::SetSpotDirection(glm::vec3 a) {
	m_SpotDirection = a;
}