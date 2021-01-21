#include "Renderer.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
	va.Bind();
	ib.Bind();
	shader.Bind();
	GL_CHECK(glEnable(GL_BLEND));
	GL_CHECK(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));//if using index buffers
	//GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 24));									  //if using normal vertices	
}
void Renderer::Clear() const {
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT));
}