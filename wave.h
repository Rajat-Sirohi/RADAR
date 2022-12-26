#ifndef WAVE_H
#define WAVE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/constants.hpp>

#include <iostream>
#include <vector>

class Wave {
public:
    glm::vec2 dir, pos = glm::vec2(0.0f);
    float speed = 10.0f;
    float duration = 0.0f;
    Wave(glm::vec2 dir);
    ~Wave();
    void draw();
    void move(float dt);
    void reflect();
    bool received();
    glm::vec2 process();
private:
    GLuint VAO, VBO;
    void updateVBO() {
        float vertices[] = { pos.x, pos.y };
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    }
};

bool OOB(Wave *w);
void pulse(std::vector<Wave*> &waves);

#endif
