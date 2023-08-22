#include "pch.h"
#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexSrc = ParseShader(vertexPath);
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
    if (!IsCompiled(vertexShader, "Vertex Shader Compilation Failed!")) return;

    std::string fragmnetSrc = ParseShader(fragmentPath);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmnetSrc);
    if (!IsCompiled(fragmentShader, "Fragmnet Shader Compilation Failed!")) return;

    m_RendererID = CreateShader(vertexShader, fragmentShader);

    if (!IsLinked())
    {
        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return;
    }

    // Always detach shaders after a successful link.
    glDetachShader(m_RendererID, vertexShader);
    glDetachShader(m_RendererID, fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, const glm::vec4& vec)
{
    glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4x4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

std::string Shader::ParseShader(const std::string& filepath)
{
    std::ifstream file(filepath);

    ASSERT(file, "Error Reading Shader Filepath: {0}", filepath);

    std::stringstream ss;

    ss << file.rdbuf();
    return ss.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);

    const GLchar* glCharSrc = source.c_str();
    glShaderSource(shader, 1, &glCharSrc, 0);

    glCompileShader(shader);

    return shader;
}

bool Shader::IsCompiled(unsigned int shader, const std::string& errorMsg)
{
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(shader);

        LOG_ERROR("{0}", infoLog.data());
        ASSERT(false, errorMsg)

        return false;
    }

    return true;
}

bool Shader::IsLinked()
{
    GLint isLinked = 0;
    glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);

    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(m_RendererID);

        LOG_ERROR("{0}", infoLog.data());
        ASSERT(false, "Shader Link Failure!")

        return false;
    }

    return true;
}

unsigned int Shader::CreateShader(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    return program;
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_RendererID, name.c_str());

    if (location == -1)
        LOG_WARN("Uniform '{0}' doesn't exist!", name);

    m_UniformLocationCache[name] = location;
    return location;
}
