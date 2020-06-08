//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#ifndef SPHERE_H_
#define SPHERE_H_

#include "includes.hpp"
#include "particule.hpp"
#include "shader.hpp"

class Sphere {
    public:
        /*
         * Constructeur: initialise la position, le rayon et la couleur de la sphère.
        */
        Sphere(glm::vec3 position, float radius, glm::vec4 color);

        /*
         * Destructeur.
        */
        virtual ~Sphere();

        /*
         * Gére la collision de la sphère avec les particules du drapeau.
        */
        void collision(std::vector<Particule> *particules);

        /*
         * Affiche la sphère à l'aide de GLUT.
        */
        void display(Shader *shader);

        /*
         * Permet le mouvement de la shpère en modifiant sa position.
        */
        void move(glm::vec3 delta);

    private:
        glm::vec4 color;
        float radius;
        glm::vec3 pos;
};

#endif /* SPHERE_H_ */
