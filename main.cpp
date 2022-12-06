#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "target.h"
#include "wave.h"

#include <iostream>
#include <vector>

#define SCR_WIDTH  800
#define SCR_HEIGHT 800
#define N_VO 1

GLFWwindow* window;
GLuint VAO[N_VO], VBO[N_VO];
Shader passthroughShader = Shader();

std::vector<Target*> targets;
std::vector<Wave*> waves;

void processInput(GLFWwindow* window) {
    glfwPollEvents();
    // if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    // }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            if (key == GLFW_KEY_R) {
                targets.push_back(new Target());
            } else if (key == GLFW_KEY_SPACE) {
                pulse(waves);
            }
        }
    }
}

void init() {
    srand(time(NULL));

    // Setup window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RADAR", NULL, NULL);
    if (window == NULL) {
	    std::cout << "Failed to create GLFW window" << std::endl;
	    glfwTerminate();
        return;
	}
    glfwMakeContextCurrent(window);

    glfwSwapInterval(0); // disable VSync, which artificially limits FPS
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	    std::cout << "Failed to initialize GLAD" << std::endl;
        return;
	}

    // Setup shader programs
    passthroughShader = Shader("shaders/passthrough.vs", "shaders/passthrough.fs");

    // Setup VAOs, VBOs
    float vertices[] = { 0.0f, 0.0f };
    glGenVertexArrays(N_VO, VAO);
    glGenBuffers(N_VO, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void update(float dt) {
    std::vector<Target*>::iterator it_t = targets.begin();
    while (it_t != targets.end()) {
        (*it_t)->move(dt);
        if (OOB(*it_t))
            targets.erase(it_t);
        else
            it_t++;
    }

    std::vector<Wave*>::iterator it_w = waves.begin();
    while (it_w != waves.end()) {
        (*it_w)->move(dt);
        if (OOB(*it_w)) {
            waves.erase(it_w);
        } else if ((*it_w)->received()) {
            // process signal
            waves.erase(it_w);
        } else {
            for (Target *target : targets) {
                if (target->contains((*it_w)->pos))
                    (*it_w)->reflect();
            }
            it_w++;
        }
    }
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    passthroughShader.use();

    glPointSize(3);
    passthroughShader.setVec3("color", glm::vec3(1.0f, 0.0f, 1.0f));
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_POINTS, 0, 1);

    passthroughShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
    for (Target *target : targets)
        target->draw();

    glPointSize(5);
    passthroughShader.setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));
    for (Wave *wave : waves)
        wave->draw();

    glfwSwapBuffers(window);
}

void run() {
    unsigned int frameCount = 0;
    float prevTime = 0, frameTime = 0;
    while (!glfwWindowShouldClose(window)) {
        float time = glfwGetTime();
        float dt = time - prevTime;
        prevTime = time;

        processInput(window);
        update(dt);
        render();

        if (time - frameTime > 0.3) {
            std::cout << "T: " << targets.size() << "\t";
            std::cout << "W: " << waves.size() << "\t";
            std::cout << "FPS: " << std::round(frameCount/(time - frameTime)) << std::endl;
            frameCount = 0;
            frameTime = time;
        }
        frameCount++;
    }
}

int main() {
    init();
    run();

    glDeleteVertexArrays(N_VO, VAO);
    glDeleteBuffers(N_VO, VBO);

    glfwTerminate();
    return 0;
}
