#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

#include "Shader.h"
#include "ErrorChecker.h"




Shader::Shader(const std::string& filepath) 
	: m_filepath(filepath) , m_RendererID(0)
{
    ShaderSource s = parseshader(filepath);
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
    std::ifstream stream(path);
    std::string line;
    enum class Stype {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::stringstream ss[2];
    Stype type = Stype::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = Stype::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = Stype::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    stream.close();
    return { ss[0].str(),ss[1].str() };

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
