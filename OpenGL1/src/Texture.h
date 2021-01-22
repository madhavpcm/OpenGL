#pragma once
#include "Renderer.h"

class Texture {
private:
	unsigned int m_RendererID;

	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_width,  m_height , m_BPP;
	std::string m_Type;
public:
	Texture(const std::string& filepath, const std::string& type );
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline int GetWidth()  { return m_width;  };
	inline int GetHeight() { return m_height; };
	std::string GetType() const { return m_Type;  }
};