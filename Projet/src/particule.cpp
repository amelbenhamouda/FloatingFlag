//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#include "../include/particule.hpp"

Particule::Particule(glm::vec3 pos, float mass, float damping, glm::vec2 texCoord) {
    this->pos = pos;
    this->lastPos = pos;
    this->mass = mass;
    this->damping = damping;
    this->texCoord = texCoord;

    force = glm::vec3(0, 0, 0);
    isStatic = false;
}

Particule::~Particule() {}

void Particule::move(glm::vec3 delta) {
    if (isStatic) {
        return;
    }
    pos += delta;
}

void Particule::step(float timeStep) {
    if (isStatic) {
        return;
    }
    //appliquer la force
    glm::vec3 temp = pos;
    pos += (pos - lastPos) * damping + (force / mass) * (timeStep / 100);
    lastPos = temp;
    force = glm::vec3(0, 0, 0);
}
