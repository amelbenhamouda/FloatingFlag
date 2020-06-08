//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#ifndef PARTICULE_H_
#define PARTICULE_H_

#include "includes.hpp"

class Particule {
    public:
        /*
         * Constructeur : initialise les variables nécéssaires pour une particule.
        */
        Particule(glm::vec3 pos, float mass, float damping, glm::vec2 texCoord);

        /*
         * Destructeur.
        */
        virtual ~Particule();

        bool isStatic;
        glm::vec3 normal;
        glm::vec3 pos;
        glm::vec3 lastPos;
        glm::vec2 texCoord;
        float damping; // amortissement
        float mass;
        glm::vec3 force;

        /*
         * Déplacement d'une particule.
        */
        void move(glm::vec3 delta);

        /*
         * Applique la force à une particule selon son statut (static ou non).
        */
        void step(float timeStep);
};

#endif /* PARTICULE_H_ */
