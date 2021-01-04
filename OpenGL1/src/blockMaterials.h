#pragma once
#include<glm/glm.hpp>
#include<vector>
#include<stdint.h>
#include<string>
class GlobalBlock
{
private:
	glm::vec3 m_AmbientStrength;
	glm::vec3 m_DiffusionFactor;
	glm::vec3 m_SpecularStrength;
public:
	GlobalBlock();
	const glm::vec3 GetAmbientStrength()  { return m_AmbientStrength; }
	const glm::vec3 GetDiffusionFactor()  { return m_DiffusionFactor; }
	const glm::vec3 GetSpecularStrength() { return m_SpecularStrength; }

	const void SetAmbientStrength(glm::vec3 a);
	const void SetDiffusionFactor(glm::vec3 a);
	const void SetSpecularStrength(glm::vec3 a);

};

class MaterialBlock : public GlobalBlock{
private:
	std::string m_BlockName;
	std::uint32_t m_ShinynessExponent;
public:
	MaterialBlock();
	const int GetshinynessExponent()	  { return m_ShinynessExponent; }
	const std::string GetBlockName()		  { return m_BlockName; }
	const void SetShinynessExponent(std::uint32_t a);
	const void SetBlockName(std::string a);

};

class FarLightBlock : public GlobalBlock {
private:
	glm::vec3 m_Direction;
public:
	FarLightBlock();
	const glm::vec3 GetDirection() { return m_Direction; }
	const void SetDirection(glm::vec3 a);
};

class PointLightBlock : public GlobalBlock {
private:
	glm::vec3 m_Position;//add the attenuation constants
public:
	PointLightBlock();
	const glm::vec3 GetPosition() { return m_Position; }
	const void SetPosition(glm::vec3 a);
};

class SpotLightBlock : public PointLightBlock{
private:
	glm::vec3 m_SpotDirection;
	float m_CutoffPhi;//needs lightdir, spotdir, phi(cutoff angle) and theta (ang between lightdir and spotdir).. some variables will be calculated inside the shader
	float m_CutoffInner;
	float m_CutoffOuter;
public:
	SpotLightBlock();
	glm::vec3 GetSpotDirection() { return m_SpotDirection; }
	
	float GetCutoffPhi() { return m_CutoffPhi; }
	float GetCutoffInner() { return m_CutoffInner; }
	float GetCutoffOuter() { return m_CutoffOuter; }

	const void SetSpotDirection(glm::vec3 a);
	const void SetCutoffPhi(float a);
	const void SetCutoffInner(float a);
	const void SetCutoffOuter(float a);
};

void readJsonFileStatic(std::vector<MaterialBlock>& database);
