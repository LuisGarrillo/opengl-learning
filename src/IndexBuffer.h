#pragma once

class IndexBuffer
{
private:
	unsigned int RendererId;
	unsigned int Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int getCount() const 
	{ 
		return Count; 
	}
};
