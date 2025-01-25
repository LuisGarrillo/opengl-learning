#pragma once
#include <string>
#include <unordered_map>

struct shaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
private:
	std::string Filepath;
	unsigned int RendererId;
	std::unordered_map<std::string, int> UniformCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform(const std::string& name, float v0, float v1, float v2, float v3);

private:
	unsigned int getUniformLocation(const std::string& name);
	shaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
};