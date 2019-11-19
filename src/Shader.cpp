#include <Shader.hpp>
#include "../external/glew-2.1.0/include/GL/glew.h"
#include "Shader.hpp"

Shader::Shader() : m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(), m_fragmentSource()
{
}


Shader::Shader(Shader const &shader)
{
    m_vertexSource = shader.m_vertexSource;
    m_fragmentSource = shader.m_fragmentSource;

    load();
}


Shader::Shader(std::string vertexSource, std::string fragmentSource) : m_vertexID(0), m_fragmentID(0), m_programID(0),
                                                                       m_vertexSource(vertexSource), m_fragmentSource(fragmentSource)
{
}


Shader::~Shader()
{
    glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
    glDeleteProgram(m_programID);
}

Shader& Shader::operator=(Shader const &shader)
{
    m_vertexSource = shader.m_vertexSource;
    m_fragmentSource = shader.m_fragmentSource;

    load();

    return *this;
}


bool Shader::load()
{
   if(glIsShader(m_vertexID) == GL_TRUE)
        glDeleteShader(m_vertexID);

    if(glIsShader(m_fragmentID) == GL_TRUE)
        glDeleteShader(m_fragmentID);

    if(glIsProgram(m_programID) == GL_TRUE)
        glDeleteProgram(m_programID);

    if(!compileShader(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
        return false;

    if(!compileShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
        return false;

    m_programID = glCreateProgram();

    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_programID, m_fragmentID);

    glBindAttribLocation(m_programID, 0, "in_Vertex");
    glBindAttribLocation(m_programID, 1, "in_Color");
    glBindAttribLocation(m_programID, 2, "in_TexCoord0");

    glLinkProgram(m_programID);

    GLint errorLink(0);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &errorLink);

    if(errorLink != GL_TRUE)
    {
        GLint errorLength(0);
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &errorLength);

        char *error = new char[errorLength + 1];

        glGetShaderInfoLog(m_programID, errorLength, &errorLength, error);
        error[errorLength] = '\0';

        std::cout << error << std::endl;

        delete[] error;
        glDeleteProgram(m_programID);

        return false;
    }

    else
        return true;
}


bool Shader::compileShader(GLuint &shader, GLenum type, std::string const &sourceFile)
{
    shader = glCreateShader(type);

    if(shader == 0)
    {
        std::cerr << "Error, no shader of type " << type << std::endl;
        return false;
    }

    std::ifstream file(sourceFile.c_str());

    if(!file)
    {
        std::cout << "Error, no such file: " << sourceFile << std::endl;
        glDeleteShader(shader);

        return false;
    }

    std::string line;
    std::string sourceCode;

    while(getline(file, line))
        sourceCode += line + '\n';

    file.close();

    const GLchar* codeSourceString = sourceCode.c_str();

    glShaderSource(shader, 1, &codeSourceString, 0);

    glCompileShader(shader);

    GLint compileError(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileError);

    if(compileError != GL_TRUE)
    {
        GLint errorLength(0);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLength);

        char *error = new char[errorLength + 1];

        glGetShaderInfoLog(shader, errorLength, &errorLength, error);
        error[errorLength] = '\0';

        std::cout << error << std::endl;

        delete[] error;
        glDeleteShader(shader);

        return false;
    }

    else
        return true;
}

GLuint Shader::getProgramID() const
{
    return m_programID;
}
