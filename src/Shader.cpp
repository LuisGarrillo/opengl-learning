#include "Shader.h"
#include "glew.h"
#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filepath) 
	: Filepath(filepath), RendererId(0)
{
    shaderProgramSource source = ParseShader(filepath);

    RendererId = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(RendererId));
}

shaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream shaders[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            shaders[(int)type] << line << '\n';
        }

    }
    return { shaders[0].str(), shaders[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* rawSource = source.c_str();
    glShaderSource(id, 1, &rawSource, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    unsigned int program = glCreateProgram();
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Shader::Bind() const 
{
    GLCall(glUseProgram(RendererId));
}
void Shader::Unbind() const 
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::SetUniform(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}


int Shader::getUniformLocation(const std::string& name) {
    if (UniformCache.find(name) != UniformCache.end())
        return UniformCache[name];

    GLCall(int location = glGetUniformLocation(RendererId, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' does not exist!" << std::endl;
    
    UniformCache[name] = location;
    return location;
}
