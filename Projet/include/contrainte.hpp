//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#ifndef CONTRAINTE_H_
#define CONTRAINTE_H_

#include "includes.hpp"
#include "particule.hpp"

struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Contrainte {
    public:
        /*
         * Constructeur qui initialise les variables de contrainte.
        */
        Contrainte(Particule *p1, Particule *p2);

        /*
         * Destructeur.
        */
        virtual ~Contrainte();

        /*
         * Fonction qui applique les contraintes si l'objet est satisfaisant.
        */
        void satisfy();

        /*
         * Affiche les contraintes (lignes) entre les particules.
        */
        void display();

    private:
        Particule *p1, *p2;
        float distance;
};

#endif /* CONTRAINTE_H_ */
