#pragma once
#include "Renderer.h"

class Texture
{
private:
	unsigned int RendererId;
	std::string Filepath;
	unsigned char* LocalBuffer;
	int Width, Height, BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int getWidth() const { return Width; }
	inline int getHeight() const { return Height; }
};