#ifndef TOOGOODENGINE_CUBE_HPP
#define TOOGOODENGINE_CUBE_HPP

// Include Windows

#ifdef WIN32
#include <GL/glew.h>


// Include Mac

#elif __APPLE__
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>


// Include UNIX/Linux

#else
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
//#include <GLES3/gl3.h>
#endif

#include <glm/glm.hpp>
#include <cstddef>
#include <Vector3.hpp>
#include <Quaternion.hpp>
#include "Shader.hpp"

using namespace TooGoodEngine;

class Cube {
private:
    GLfloat m_vertices[72] = {
            .5f, .5f, .5f, -.5f, .5f, .5f, -.5f, -.5f, .5f, .5f, -.5f, .5f, // v0,v1,v2,v3 (front)
            .5f, .5f, .5f, .5f, -.5f, .5f, .5f, -.5f, -.5f, .5f, .5f, -.5f, // v0,v3,v4,v5 (right)
            .5f, .5f, .5f, .5f, .5f, -.5f, -.5f, .5f, -.5f, -.5f, .5f, .5f, // v0,v5,v6,v1 (top)
            -.5f, .5f, .5f, -.5f, .5f, -.5f, -.5f, -.5f, -.5f, -.5f, -.5f, .5f, // v1,v6,v7,v2 (left)
            -.5f, -.5f, -.5f, .5f, -.5f, -.5f, .5f, -.5f, .5f, -.5f, -.5f, .5f, // v7,v4,v3,v2 (bottom)
            .5f, -.5f, -.5f, -.5f, -.5f, -.5f, -.5f, .5f, -.5f, .5f, .5f, -.5f  // v4,v7,v6,v5 (back)
    };

    GLfloat vertices[72] = {
            .5f, .5f, .5f, -.5f, .5f, .5f, -.5f, -.5f, .5f, .5f, -.5f, .5f, // v0,v1,v2,v3 (front)
            .5f, .5f, .5f, .5f, -.5f, .5f, .5f, -.5f, -.5f, .5f, .5f, -.5f, // v0,v3,v4,v5 (right)
            .5f, .5f, .5f, .5f, .5f, -.5f, -.5f, .5f, -.5f, -.5f, .5f, .5f, // v0,v5,v6,v1 (top)
            -.5f, .5f, .5f, -.5f, .5f, -.5f, -.5f, -.5f, -.5f, -.5f, -.5f, .5f, // v1,v6,v7,v2 (left)
            -.5f, -.5f, -.5f, .5f, -.5f, -.5f, .5f, -.5f, .5f, -.5f, -.5f, .5f, // v7,v4,v3,v2 (bottom)
            .5f, -.5f, -.5f, -.5f, -.5f, -.5f, -.5f, .5f, -.5f, .5f, .5f, -.5f  // v4,v7,v6,v5 (back)
    };

    // colour array
    GLfloat m_colors[72] = {
            1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1,  // v0,v1,v2,v3 (front)
            1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1,  // v0,v3,v4,v5 (right)
            1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0,  // v0,v5,v6,v1 (top)
            1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,  // v1,v6,v7,v2 (left)
            0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0,  // v7,v4,v3,v2 (bottom)
            0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1   // v4,v7,v6,v5 (back)
    };

    // index array for glDrawElements()
    // A cube requires 36 indices = 6 sides * 2 tris * 3 verts
    GLuint m_indices[36] = {
            0, 1, 2, 2, 3, 0,    // v0-v1-v2, v2-v3-v0 (front)
            4, 5, 6, 6, 7, 4,    // v0-v3-v4, v4-v5-v0 (right)
            8, 9, 10, 10, 11, 8,    // v0-v5-v6, v6-v1-v0 (top)
            12, 13, 14, 14, 15, 12,    // v1-v6-v7, v7-v2-v1 (left)
            16, 17, 18, 18, 19, 16,    // v7-v4-v3, v3-v2-v7 (bottom)
            20, 21, 22, 22, 23, 20     // v4-v7-v6, v6-v5-v4 (back)
    };

    size_t vertices_size = 72;
    size_t colors_size = 72;
    size_t indices_size = 36;

    GLuint vboID = 0;
    GLuint iboID = 0;

    Shader shader;

public:
    explicit Cube(float size, std::string vert, std::string frag);

    void prepare(Vector3 position, Quaternion orientation);
    void display(glm::mat4& projection, glm::mat4& modelview);
};
#endif //TOOGOODENGINE_CUBE_HPP
