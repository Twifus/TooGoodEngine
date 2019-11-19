#include <Cube.hpp>

#include <glm/gtc/type_ptr.hpp>

Cube::Cube(float size, std::string vert, std::string frag) {
    if (size != 1)
        for (size_t i = 0; i < vertices_size; ++i)
            m_vertices[i] *= size;

    shader = Shader(vert, frag);

    shader.load();

    glGenBuffers(1, &vboID);
    glGenBuffers(1, &iboID);
}

void Cube::prepare(Vector3 position, Quaternion orientation) {

}

void Cube::display(glm::mat4& projection, glm::mat4& modelview) {
    glUseProgram(shader.getProgramID());

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, vertices_size + colors_size, 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_size, vertices);
    glBufferSubData(GL_ARRAY_BUFFER, vertices_size, colors_size, m_colors);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, m_indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // draw
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, nullptr);
    glColorPointer(3, GL_FLOAT, 0, (void*) vertices_size);

    glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

    glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, nullptr);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUseProgram(0);
}
