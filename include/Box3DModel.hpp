#pragma once

#include "Graph3DModel.hpp"

namespace TooGoodEngine {

    class Box3DModel : public Graph3DModel {

    private:
        Vector3 dimensions;
        Vector3 color = Vector3(1.,1.,1.);

        const GLuint m_indices[36] = {
                0, 1, 2, 1, 2, 3,
                4, 5, 6, 5, 6, 7,
                0, 1, 4, 1, 4, 5,
                2, 3, 6, 3, 6, 7,
                0, 2, 4, 2, 4, 6,
                1, 3, 5, 3, 5, 7
        };
    public:
        explicit Box3DModel(Vector3& dimensions);
        Box3DModel(Vector3& dimensions, Vector3& color);

        ~Box3DModel();

        void prepare(Vector3 position, Quaternion orientation) override;
    };
}