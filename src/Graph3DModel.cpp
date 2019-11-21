#include <Graph3DModel.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace TooGoodEngine {
    Graph3DModel::Graph3DModel() {
        glGenVertexArrays(1, &vaoID);
        glGenBuffers(1, &vboID);
        glGenBuffers(1, &iboID);

        shader = Shader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
        shader.load();
    }

    void Graph3DModel::display(glm::mat4 &projection, glm::mat4 &modelview) {
        glUseProgram(shader.getProgramID());

        std::cout << __FUNCTION__ << std::endl;
        for (int i = 0; i < 8; ++i) {
            std::cout << "[x: " << vertices[6*i + 0] << ", y: " << vertices[6*i + 1] << ",z: " << vertices[6*i + 2] << "]" << std::endl;
        }

        glBindVertexArray(vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "projection"), 1, GL_FALSE,
                           value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glUseProgram(0);
    }
}