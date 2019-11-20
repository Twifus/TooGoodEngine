#ifndef TOOGOODENGINE_CUBE_HPP
#define TOOGOODENGINE_CUBE_HPP

// Include Windows

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

#include <glm/glm.hpp>
#include <cstddef>
#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Shader.hpp"

using namespace TooGoodEngine;

class Cube {
private:
    GLfloat m_vertices[48] = {
            .5f, .5f, .5f,      1.f, 1.f, 1.f,
            .5f, .5f, -.5f,     1.f, 1.f, 0.f,
            .5f, -.5f, .5f,     1.f, 0.f, 1.f,
            .5f, -.5f, -.5f,    1.f, 0.f, 0.f,
            -.5f, .5f, .5f,     0.f, 1.f, 1.f,
            .5f, .5f, -.5f,     0.f, 1.f, 0.f,
            -.5f, -.5f, .5f,    0.f, 0.f, 1.f,
            -.5f, -.5f, -.5f,   1.f, 1.f, 0.f,
    };

    GLfloat vertices[48] = {
            .5f, .5f, .5f,      1.f, 1.f, 1.f,
            .5f, .5f, -.5f,     1.f, 1.f, 0.f,
            .5f, -.5f, .5f,     1.f, 0.f, 1.f,
            .5f, -.5f, -.5f,    1.f, 0.f, 0.f,
            -.5f, .5f, .5f,     0.f, 1.f, 1.f,
            -.5f, .5f, -.5f,    0.f, 1.f, 0.f,
            -.5f, -.5f, .5f,    0.f, 0.f, 1.f,
            -.5f, -.5f, -.5f,   0.f, 0.f, 0.f,
    };

    // colour array
    /*GLfloat m_colors[24] = {
            1.f, 0.f, 0.f,      1.f, 0.f, 0.f,
            1.f, 0.f, 0.f,      1.f, 0.f, 0.f,
            1.f, 0.f, 0.f,      1.f, 0.f, 0.f,
            1.f, 0.f, 0.f,      1.f, 0.f, 0.f
    };*/

    // index array for glDrawElements()
    // A cube requires 36 indices = 6 sides * 2 tris * 3 verts
    GLuint m_indices[36] = {
            0, 1, 2, 1, 2, 3,
            4, 5, 6, 5, 6, 7,
            0, 1, 4, 1, 4, 5,
            2, 3, 6, 3, 6, 7,
            0, 2, 4, 2, 4, 6,
            1, 3, 5, 3, 5, 7
    };

    size_t vertices_size = 48 * sizeof(GLfloat);
    //size_t colors_size = 24 * sizeof(GLfloat);
    size_t indices_size = 36 * sizeof(GLuint);

    GLuint vboID = 0;
    GLuint iboID = 0;
    GLuint vaoID = 0;

    Shader shader;

public:
    explicit Cube(float size, std::string vert, std::string frag);

    void prepare(Vector3 position, Quaternion orientation);
    void display(glm::mat4& projection, glm::mat4& modelview);
};
#endif //TOOGOODENGINE_CUBE_HPP
