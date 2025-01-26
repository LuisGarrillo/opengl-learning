#pragma once

#include <glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearErrors;\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearErrors();

bool GLLogCall(const char* function, const char* file, int line);

struct vec2 {
    float x;
    float y;
};

class Renderer
{
private:
    //VertexArray VertexArrayR;
    unsigned int WindowWidth;
    unsigned int WindowHeight;
public:
    Renderer(unsigned int width, unsigned int height);
    //void DrawRectangle(vec2 position, float width, float height);
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
private:
    vec2 normalizePosition(vec2 position) const;
};