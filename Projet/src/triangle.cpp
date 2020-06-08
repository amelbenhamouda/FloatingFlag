//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#include "../include/triangle.hpp"

Triangle::Triangle(Particule* p1, Particule* p2, Particule* p3) {
    particules[0] = p1;
    particules[1] = p2;
    particules[2] = p3;
}

void Triangle::display() {
    for (int i = 0; i < 3; i++) {
        glTexCoord2fv(glm::value_ptr(particules[i]->texCoord));
        glNormal3fv(glm::value_ptr(particules[i]->normal));
        glVertex3fv(glm::value_ptr(particules[i]->pos));
    }
}

Triangle::~Triangle() {}
