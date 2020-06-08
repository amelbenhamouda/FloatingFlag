//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "particule.hpp"

class Triangle {
    public:
        /*
         * Constructeur qui intialise un tableau de 3 particules.
        */
        Triangle(Particule* p1, Particule* p2, Particule* p3);

        /*
         * Destructeur.
        */
        virtual ~Triangle();

        /*
         * Affiche chaque particule du triangle.
        */
        void display();

        Particule* particules[3];
};

#endif /* TRIANGLE_H_ */
