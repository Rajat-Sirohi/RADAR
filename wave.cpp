#include "wave.h"

#define EPS 0.001

Wave::Wave(glm::vec2 direction) : dir(glm::normalize(direction)) {
    // Setup VAO, VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    updateVBO();

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

Wave::~Wave() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Wave::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 1);
}

void Wave::move(float dt) {
    duration += dt;
    pos += dir * speed * dt;
    updateVBO();
}

void Wave::reflect() {
    dir = -dir;
}

bool Wave::received() {
    return glm::length2(pos) < EPS && glm::dot(pos, dir) < 0;
}

glm::vec2 Wave::process() {
    return -3.0f * dir;
}

bool OOB(Wave *w) {
    return (w->pos.x < -1) || (w->pos.x > 1) || (w->pos.y < -1) || (w->pos.y > 1);
}

void pulse(std::vector<Wave*> &waves) {
    for (float i = 0; i < 1; i += 0.01) {
        float angle = i * 2*glm::pi<float>();
        glm::vec2 dir(glm::cos(angle), glm::sin(angle));
        waves.push_back(new Wave(dir));
    }
}
