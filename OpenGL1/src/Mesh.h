#pragma once
#include<vector>
#include<string>
#include<glm/glm.hpp>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Renderer.h"
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
struct MeshTexture {
	uint32_t id;
	std::string type;
};

class Mesh{
public:
	std::vector<Vertex> m_Vertices;
	std::vector<Texture> m_Textures;
	std::vector<uint32_t> m_Indices;

	Mesh(const std::vector<Vertex>& vertices,
		 const std::vector<Texture>& textures,
		 const  std::vector<uint32_t> &indices);

	void Draw(Shader& shader);
private:
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer m_EBO;
	Renderer m_RO;

	void setupMesh();
};

