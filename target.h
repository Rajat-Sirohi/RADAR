#ifndef TARGET_H
#define TARGET_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

#include "random.h"

class Target {
public:
    glm::vec2 pos, vel;
    float size;
    Target(glm::vec2 pos, glm::vec2 vel, float size);
    Target(glm::vec2 pos, glm::vec2 vel) : Target(pos, vel, 0.05f) {}
    Target(glm::vec2 pos) : Target(pos, RAND_DIR()) {}
    Target() : Target(glm::vec2(RAND_M(0.3, 0.5), RAND_M(0.3, 0.5))) {}
    ~Target();
    void draw();
    void move(float dt);
    bool contains(glm::vec2 p);
private:
    GLuint VAO, VBO;
    void updateVBO() {
        float vertices[] = {
            pos.x - size, pos.y - size,
            pos.x - size, pos.y + size,
            pos.x + size, pos.y - size,
            pos.x + size, pos.y + size,
        };
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    }
};

bool OOB(Target *t);

#endif
