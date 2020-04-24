#include"VertexBuffer.h"
#include "ErrorChecker.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size) 
{
    GL_CHECK(glGenBuffers(1, &m_RendererID));//we say buffer 1 has to be made and connect it to a intger variable int buffer
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER,m_RendererID));//now int buffer points to a standard array buffer
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW));//size in bytes( check documentation ) glenum usage indiacates type of usage (static or dynamic or stream)
}
VertexBuffer::~VertexBuffer() 
{
    GL_CHECK(glDeleteBuffers(1, &m_RendererID));
}
void VertexBuffer::Bind()const 
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}
void VertexBuffer:: UnBind() const 
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}