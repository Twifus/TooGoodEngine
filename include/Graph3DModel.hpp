#pragma once

#ifdef WIN32
#include <GL/glew.h>

// Include Mac

#elif __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>


// Include UNIX/Linux

#else
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
#endif

#include "Shader.hpp"
#include <glm/glm.hpp>
#include "Quaternion.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine {

    class Graph3DModel {

    protected:
        GLfloat *vertices = nullptr;
        GLuint *indices = nullptr;

        size_t vertices_size = 0;
        size_t indices_size = 0;

        GLuint vboID = 0;
        GLuint iboID = 0;
        GLuint vaoID = 0;

        Shader shader;

    public:
        Graph3DModel();

        virtual void prepare(Vector3 position, Quaternion orientation) = 0;

        virtual void display(glm::mat4 &projection, glm::mat4 &modelview);
    };
}