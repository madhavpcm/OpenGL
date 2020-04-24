#include<GL/glew.h>
#include"ErrorChecker.h"
#include<iostream>
void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cout << "OpenGL error " << err << " at " << fname << ": " << line << " for " << stmt << std::endl;
    }
}