#ifndef TARGET_H
#define TARGET_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>

#define RAND_F (float(std::rand()) / float(RAND_MAX))

class Target {
public:
    glm::vec2 pos, vel;
    float size;
    Target(glm::vec2 pos, glm::vec2 vel, float size);
    Target(glm::vec2 pos, glm::vec2 vel) : Target(pos, vel, 0.05f) {}
    Target(glm::vec2 pos) : Target(pos, glm::vec2(2*RAND_F-1, 2*RAND_F-1)) {}
    Target() : Target(glm::vec2(RAND_F-0.5, RAND_F-0.5)) {}
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
