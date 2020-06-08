//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#include "../include/contrainte.hpp"

Contrainte::Contrainte(Particule *p1, Particule *p2) {
    this->p1 = p1;
    this->p2 = p2;
    distance = glm::length(p1->pos - p2->pos);
}

Contrainte::~Contrainte() {}

void Contrainte::satisfy() {
    glm::vec3 v = p1->pos - p2->pos;
    v *= ((1.0f - distance / glm::length(v)) * 0.8f);
    p1->move(-v);
    p2->move(v);
}

void Contrainte::display() {
    glBegin(GL_LINES);
    glVertex3fv(glm::value_ptr(p1->pos));
    glVertex3fv(glm::value_ptr(p2->pos));
    glEnd();
}
