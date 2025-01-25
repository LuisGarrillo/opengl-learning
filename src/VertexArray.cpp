#include "VertexArray.h"

VertexArray::VertexArray() 
{
	glGenVertexArrays(1, &RendererId);
}

VertexArray::~VertexArray() 
{
	glDeleteVertexArrays(1, &RendererId);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) 
	{
		const auto element = elements[i];
		glVertexAttribPointer(
			i, element.count, element.type, element.normalized, layout.getStride(), (const void*) offset
		);
		glEnableVertexAttribArray(i);
		offset += element.count * VertexBufferElement:: getSizeOfType(element.type);
	}
}

void VertexArray::Bind() const {
	glBindVertexArray(RendererId);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}