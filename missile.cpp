#include "missile.h"

Missile::Missile(glm::vec2 velocity, glm::vec2 position) : vel(velocity), pos(position) {
    // Setup VAO, VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    updateVBO();

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

Missile::~Missile() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Missile::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 1);
}

void Missile::move(float dt) {
    pos += vel * dt;
    updateVBO();
}

bool OOB(Missile *m) {
    return (m->pos.x < -1) || (m->pos.x > 1) || (m->pos.y < -1) || (m->pos.y > 1);
}
