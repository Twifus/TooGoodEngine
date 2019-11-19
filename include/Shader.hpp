#ifndef DEF_SHADER
#define DEF_SHADER


// Include Windows

#ifdef WIN32
#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>


// Include Mac

#elif __APPLE__
#include <OpenGL/gl3.h>


// Include UNIX/Linux

#else
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>

#endif


#include <iostream>
#include <string>
#include <fstream>

class Shader
{
    public:

    Shader();
    Shader(Shader const &shader);
    Shader(std::string vertexSource, std::string fragmentSource);
    ~Shader();

    Shader& operator=(Shader const &shader);

    bool load();
    bool compileShader(GLuint &shader, GLenum type, std::string const &sourceFile);
    [[nodiscard]] GLuint getProgramID() const;


    private:

    GLuint m_vertexID;
    GLuint m_fragmentID;
    GLuint m_programID;

    std::string m_vertexSource;
    std::string m_fragmentSource;
};

#endif
