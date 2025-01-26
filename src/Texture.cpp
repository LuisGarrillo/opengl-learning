#include "Texture.h"
#include "vendor/stb_image/stb_image.h"


Texture::Texture(const std::string& path)
	:RendererId(0), Filepath(path), LocalBuffer(nullptr), Width(0), Height(0), BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	LocalBuffer = stbi_load(path.c_str(), &Width, &Height, &BPP, 4);

	glGenTextures(1, &RendererId);
	glBindTexture(GL_TEXTURE_2D, RendererId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (LocalBuffer)
		stbi_image_free(LocalBuffer);

}
Texture::~Texture()
{
	glDeleteTextures(1, &RendererId);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, RendererId);
}
void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}