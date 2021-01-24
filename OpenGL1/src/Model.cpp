#pragma once
#include <iostream>
#include "Model.h"

void Model::Draw(Shader& shader)
{
	for (auto& i : m_Meshes) {
		i.Draw(shader);
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ASSIMP::ERROR::" << importer.GetErrorString() << std::endl;
	}
	m_Directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);

}	

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (uint32_t i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(processMesh(mesh, scene));
	}
	for (uint32_t i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	std::vector<uint32_t> indices;

	for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 position= glm::vec3(mesh->mVertices[i].x,
									mesh->mVertices[i].y,
									mesh->mVertices[i].z );
		vertex.Position = position;
		glm::vec3 normal =glm::vec3(mesh->mNormals[i].x,
									mesh->mNormals[i].y,
									mesh->mNormals[i].z);
		vertex.Normal = normal;
		if (mesh->mTextureCoords) {
			glm::vec2 texture = glm::vec2(mesh->mTextureCoords[0][i].x,
										  mesh->mTextureCoords[0][i].y);
			vertex.TexCoords = texture;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		
		for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (uint32_t ii = 0; ii < face.mNumIndices; ii++) {
				indices.push_back(face.mIndices[ii]);
			}
		}
		
	}
	return Mesh(vertices, textures, indices);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	return std::vector<Texture>();
}
