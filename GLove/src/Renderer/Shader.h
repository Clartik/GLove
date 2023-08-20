#pragma once

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, const glm::vec4& vec);
	void SetUniformMat4f(const std::string& name, const glm::mat4x4& matrix);
private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	bool IsCompiled(unsigned int shader, const std::string& errorMsg);

	unsigned int CreateShader(unsigned int vertexShader, unsigned int fragmentShader);

	int GetUniformLocation(const std::string& name);
private:
	unsigned int m_RendererID;

	std::unordered_map<std::string, int> m_UniformLocationCache;
};