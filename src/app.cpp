#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    GLenum err = glewInit();
    if (err != GLEW_OK)
        return -1;
    {

        float dataArr[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,

            -0.5f,  0.5f,
        };

        unsigned int indicesArr[] = {
            0, 1, 2,
            2, 3, 0
        };

        // Create Vertex Array Object
        unsigned int vertexAO;
        glGenVertexArrays(1, &vertexAO);
        glBindVertexArray(vertexAO);


        // Create Vertex Buffer
        VertexArray va;
        VertexBuffer vb(dataArr, sizeof(float) * 2 * 4);

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        // Create Index Buffer
        IndexBuffer ib(indicesArr, 6);

        // Create Shader
        Shader shader("res/shaders/Basic.shader");
        shader.Bind();

        // Get uniform
        shader.SetUniform("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        float r = 0.0f;
        float increment = 0.5f;

        // Unbound everything
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            // bind shader
            shader.Bind();
            shader.SetUniform("u_Color", r, 0.3f, 0.8f, 1.0f);

            va.Bind();
            ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));


            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;
            r += increment;


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}