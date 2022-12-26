#ifndef MISSILE_H
#define MISSILE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>

class Missile {
public:
    glm::vec2 pos, vel;
    float speed = 2.0f;
    Missile(glm::vec2 target, glm::vec2 pos);
    Missile(glm::vec2 target) : Missile(target, glm::vec2(0.0f)) {}
    ~Missile();
    void draw();
    void move(float dt);
    void update_target(glm::vec2 target);
private:
    GLuint VAO, VBO;
    void updateVBO() {
        float vertices[] = { pos.x, pos.y };
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    }
};

bool OOB(Missile *m);

#endif
