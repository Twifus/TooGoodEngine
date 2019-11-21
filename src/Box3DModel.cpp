#include <Box3DModel.hpp>

namespace TooGoodEngine {

    Box3DModel::Box3DModel(TooGoodEngine::Vector3& dimensions) : Graph3DModel(), dimensions(dimensions) {
        vertices = new GLfloat[48];
        vertices_size = 48 * sizeof(GLfloat);
        indices = new GLuint[36];
        for (size_t i = 0; i < 36; ++i)
            indices[i] = m_indices[i];
    }

    Box3DModel::Box3DModel(Vector3& dimensions, Vector3& color) : Graph3DModel(), dimensions(dimensions), color(color) {
        vertices = new GLfloat[48];
        vertices_size = 48 * sizeof(GLfloat);
        indices = new GLuint[36];
        for (size_t i = 0; i < 36; ++i)
            indices[i] = m_indices[i];
    }

    Box3DModel::~Box3DModel() {
        delete[] vertices;
        delete[] indices;
    }

    void Box3DModel::prepare(TooGoodEngine::Vector3 position, TooGoodEngine::Quaternion orientation) {
        double vertexNorm = dimensions.Magnitude() / 2;
        for (size_t i = 0; i < 8; ++i) {
            Vector3 vertex = dimensions;
            if ((i & (unsigned int) 1) != 0)
                vertex.z *= -1;
            if ((i & (unsigned int) 2) != 0)
                vertex.y *= -1;
            if ((i & (unsigned int) 4) != 0)
                vertex.x *= -1;
            vertex = orientation * vertex;
            vertex = vertex.Normalized();
            vertex *= vertexNorm;
            vertex += position;
            vertices[6*i + 0] = (GLfloat) vertex.x;
            vertices[6*i + 1] = (GLfloat) vertex.y;
            vertices[6*i + 2] = (GLfloat) vertex.z;
            vertices[6*i + 3] = (GLfloat) color.x;
            assert(vertices[6*i + 3] <= 1);
            vertices[6*i + 4] = (GLfloat) color.y;
            assert(vertices[6*i + 4] <= 1);
            vertices[6*i + 5] = (GLfloat) color.z;
            assert(vertices[6*i + 5] <= 1);
        }
    }
}