#pragma once
#include "Mesh.h"
#include<vector>
#include<string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	Model(char *path) {
		loadModel(path);
	}
	void Draw(Shader& shader);
private:
	std::vector<Mesh> m_Meshes;
	std::string m_Directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);


};

