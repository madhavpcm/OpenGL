#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <streambuf>
#include "Shader.h"
#include "ErrorChecker.h"
namespace fs = std::filesystem;

Shader::Shader(const std::string& filepath) 
	: m_filepath(filepath) , m_RendererID(0)
{
    ShaderSource s = parseshader(filepath);
    //std::cout << "\n" << s.vSource << "\n" << s.fSource;
    m_RendererID = createShader(s.vSource, s.fSource);

}
Shader::~Shader() 
{
    GL_CHECK(glDeleteProgram(m_RendererID));
}
void Shader::Bind() const {
    GL_CHECK(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GL_CHECK(glUseProgram(0));
}
void Shader::setUniform1f(const std::string& name, float v0) {
    GL_CHECK(glUniform1f(GetUniformLocation(name), v0));
}
void Shader::setUniform1i(const std::string& name, int i0) {
    GL_CHECK(glUniform1i(GetUniformLocation(name), i0));
}
void Shader::setUniform2f(const std::string& name, float v0, float v1) {
    GL_CHECK(glUniform2f(GetUniformLocation(name), v0, v1 ));
}
void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2) {
    GL_CHECK(glUniform3f(GetUniformLocation(name), v0, v1, v2));

}
void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    GL_CHECK(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}
void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix) {
    GL_CHECK(glUniformMatrix4fv(GetUniformLocation(name), 1 , GL_FALSE , &matrix[0][0]));
}
void Shader::setUniformvec3(const std::string& name, glm::vec3 v) {
    GL_CHECK(glUniform3f(GetUniformLocation(name), v.x, v.y ,v.z));
}
void Shader::setUniformblock_Material(block_Materials& b) {

    setUniformvec3("block.ambientStrength",  b.getAmbientStrength());
    setUniformvec3("block.diffusionFactor",  b.getDiffusionFactor());
    setUniformvec3("block.specularStrength", b.getSpecularStrength());
    setUniform1i("block.shineExp", b.getshinynessExponent());

}

int Shader::GetUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }
    else{
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        if (location == -1)
            std::cout << " Warning illegal location requested , check the uniform name :: [" << name << "] again  " << std::endl;
        else
            m_UniformLocationCache[name] = location; 
        return location;
    }
    
}

 ShaderSource Shader::parseshader(const std::string& path) {
    std::string ss[2];//0 for vertex, 1 for fragment

    for (const auto& entry : fs::directory_iterator(path)) {//fetch all files of a shader directory(can be improved )
        std::ifstream t(entry.path().string());
        std::string str((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
        std::cout << entry.path().string()<<std::endl;
        if (entry.path().string().find("vertex") != std::string::npos) {
            ss[0] = str;
            std::cout << ss[0] << "vertex" << std::endl;
        }
        else if (entry.path().string().find("fragment")!= std::string::npos) {
            ss[1] = str;
            std::cout << ss[1] << "fragment" << std::endl;
        }
    }

    return { ss[0],ss[1]};

}
 unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
 unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    //ERROR HANDLING
    int res;
    glGetShaderiv(id, GL_COMPILE_STATUS, &res);

    if (res == GL_FALSE) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* mes = (char*)alloca(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, mes);
        std::cout << " Compilation of" << (type == GL_VERTEX_SHADER ? " vertex" : " fragment") << " shader failed !" << std::endl;
        std::cout << mes << std::endl;

        glDeleteShader(id);
        return 0;

    }

    return id;
}
