#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <glm/glm.hpp>

#define RAND_F (float(std::rand()) / float(RAND_MAX))
#define RAND_R(a,b) (RAND_F * ((b)-(a)) + (a))

/* Returns random float between (-b, b) excluding (-a, a) */
inline float RAND_M(float a, float b) {
    if (RAND_F < 0.5)
        return RAND_R(a, b);
    else
        return -RAND_R(a, b);
}

inline glm::vec2 RAND_DIR() {
    float angle = RAND_F;
    return glm::vec2(glm::cos(angle), glm::sin(angle));
}

#endif
