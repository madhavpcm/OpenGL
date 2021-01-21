#include "Texture.h"
#include <stbimage/stb_image.h>

Texture::Texture(const std::string& filepath )
	:m_RendererID(0),m_FilePath(filepath), m_LocalBuffer(nullptr), m_width(0) , m_height(0), m_BPP(0) 
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(filepath.c_str(), &m_width , &m_height , &m_BPP , 4);
	GL_CHECK(glGenTextures(1, &m_RendererID));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));

	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA ,GL_UNSIGNED_BYTE , m_LocalBuffer));
	GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}
}
Texture::~Texture() {
	GL_CHECK(glDeleteTextures(1, &m_RendererID));
}
void Texture::Bind(unsigned int slot) const {
	GL_CHECK(glActiveTexture(GL_TEXTURE0 + slot));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}
void Texture::UnBind() const {
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}