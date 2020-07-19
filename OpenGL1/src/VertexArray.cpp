#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "ErrorChecker.h"
void VertexArray::Bind() const 
{
	GL_CHECK(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const
{
	GL_CHECK(glBindVertexArray(0));
}

VertexArray::VertexArray() 
{
	GL_CHECK(glGenVertexArrays(1, &m_RendererID));
	GL_CHECK(glBindVertexArray(m_RendererID));
}
VertexArray::~VertexArray() 
{
	GL_CHECK(glDeleteVertexArrays(1, &m_RendererID));
}
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	unsigned int offset = 0;
	const auto& elements = layout.GetElements();

	for (unsigned int i= 0; i < elements.size(); i++) {
		const auto& ele = elements[i];
		GL_CHECK(glEnableVertexAttribArray(i));
		GL_CHECK(glVertexAttribPointer(i,ele.count,ele.type, ele.normalized,layout.GetStride(), (const void*)offset));/*vertex can hold alot of data other than coordinates, and
																			thereby increasing the size. */
		offset += ele.count *ele.GetSizeOfType(ele.type);
	}
}