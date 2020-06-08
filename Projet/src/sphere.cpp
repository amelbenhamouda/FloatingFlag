//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#include "../include/sphere.hpp"

Sphere::Sphere(glm::vec3 position, float radius, glm::vec4 color) {
    this->pos = position;
    this->radius = radius;
    this->color = color;
}

Sphere::~Sphere() {}

void Sphere::collision(std::vector<Particule> *particules) {
    for (std::vector<Particule>::size_type i = 0; i < particules->size(); i++) {
        glm::vec3 v = (*particules)[i].pos - pos;
        float distance = glm::length(v);
        if (distance < radius) {
            (*particules)[i].pos += glm::normalize(v)*(radius-distance);
        }
    }
}

void Sphere::display(Shader *shader) {
    shader->setModelMatrix(glm::translate(pos));
    glColor3f(0.5f, 1.0f, 1.0f);
    glutWireSphere(radius, 30, 30);
    //glutSolidSphere(radius, 30, 30); 
}

void Sphere::move(glm::vec3 delta) {
    pos += delta;
}
