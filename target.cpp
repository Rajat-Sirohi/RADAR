#include "target.h"

Target::Target(glm::vec2 position, glm::vec2 velocity, float size) : pos(position), vel(velocity), size(size) {
    // Setup VAO, VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    updateVBO();

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

Target::~Target() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Target::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Target::move(float dt) {
    pos += vel * dt;
    updateVBO();
}

bool Target::contains(glm::vec2 p) {
    return (p.x > pos.x - size) && (p.x < pos.x + size)
        && (p.y > pos.y - size) && (p.y < pos.y + size);
}

bool OOB(Target *t) {
    return (t->pos.x + t->size < -1) || (t->pos.x - t->size > 1)
        || (t->pos.y + t->size < -1) || (t->pos.y - t->size > 1);
}
