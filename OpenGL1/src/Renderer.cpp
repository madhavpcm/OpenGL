#include "Renderer.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
	va.Bind();
	ib.Bind();
	shader.Bind();
	GL_CHECK(glDisable(GL_BLEND));
	//GL_CHECK(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 36));
}
void Renderer::Clear() const {
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
}