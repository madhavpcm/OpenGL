#include"IndexBuffer.h"
#include "ErrorChecker.h"


IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) 
    : m_Count(count)
{   GL_CHECK(glGenBuffers(1, &m_RendererID));//we say buffer 1 has to be made and connect it to a intger variable int buffer
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));//now int buffer points to a standard array buffer
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));//size in bytes( check documentation ) glenum usage indiacates type of usage (static or dynamic or stream)
}
IndexBuffer::~IndexBuffer()
{
    GL_CHECK(glDeleteBuffers(1, &m_RendererID));
}
void IndexBuffer::Bind() const
{
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}
void IndexBuffer::UnBind() const
{
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}