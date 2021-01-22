#include "Mesh.h"
#include "ErrorChecker.h"
Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<Texture>& textures, const std::vector<uint32_t> &indices)
	:m_Vertices(vertices),m_Textures(textures),m_Indices(indices),
	m_VBO(vertices.data(),vertices.size()*sizeof(Vertex)),
	m_EBO(indices.data(),indices.size()*sizeof(uint32_t))
{
	setupMesh();//vector.data() is same as &vector[0]
}
void Mesh::Draw(Shader& shader)
{
	uint32_t diffuseNr = 1;
	uint32_t specularNr = 1;
	uint32_t emissionNr = 1;
	for (uint32_t i = 0; i < m_Textures.size(); i++) {
		m_Textures[i].Bind();

		std::string number;
		std::string base = m_Textures[i].GetType();

		if (base == "diffuse") {
			number = std::to_string(diffuseNr++);
		}
		else if (base == "texture_specular") {
			number = std::to_string(specularNr++);
		}
		else if (base == "texture_emission") {
			number = std::to_string(emissionNr++);
		}

		shader.setUniform1f(("texture_Material." + base + number).c_str(), i);
	}
	m_RO.Draw(m_VAO, m_EBO, shader);
	m_VAO.UnBind();
}
void Mesh::setupMesh() {
	m_VAO.Bind();
	m_VBO.Bind();
	m_EBO.Bind();

	VertexBufferLayout layout;
	layout.Push<float>(3);//Position
	layout.Push<float>(3);//Normal
	layout.Push<float>(2);//texturecoord

	m_VAO.AddBuffer(m_VBO, layout);

	m_VAO.UnBind();
}
