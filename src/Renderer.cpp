#include "Renderer.h"
#include <iostream>

void GLClearErrors()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " <<
            function << " " << file << ": " << line << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer(unsigned int width, unsigned int height) {
    WindowWidth = width;
    WindowHeight = height;
}

vec2 Renderer::normalizePosition(vec2 position) const
{
    return { position.x /WindowWidth, position.y / WindowHeight };
}
/*
void Renderer::DrawRectangle(vec2 position, float width, float height) 
{
    float dataArr[8];

    for (unsigned int i = 0; i < 4; i++)
    {
        switch(i)
        {
            case 0: {
                vec2 normalizedPosition = normalizePosition({ position.x, position.y});
                dataArr[0] = normalizedPosition.x;
                dataArr[1] = normalizedPosition.y;
                break;
            }
            case 1: {
                vec2 normalizedPosition = normalizePosition({ position.x + width, position.y });
                dataArr[2] = normalizedPosition.x;
                dataArr[3] = normalizedPosition.y;
                break;
            }
            case 2: {
                vec2 normalizedPosition = normalizePosition({ position.x + width, position.y + height });
                dataArr[4] = normalizedPosition.x;
                dataArr[5] = normalizedPosition.y;
                break;
            }
            case 3: {
                vec2 normalizedPosition = normalizePosition({ position.x, position.y + height });
                dataArr[6] = normalizedPosition.x;
                dataArr[7] = normalizedPosition.y;
                break;
            }
        }
    }

    unsigned int indicesArr[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    VertexBuffer vb(dataArr, sizeof(float) * 2 * 4);
    
    VertexBufferLayout layout;
    layout.Push<float>(2);
    VertexArrayR.AddBuffer(vb, layout);

    // Create Index Buffer
    IndexBuffer ib(indicesArr, 6);

    // Create Shader
    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    

    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}
*/
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();

    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}