#ifndef FLAG_H_
#define FLAG_H_

//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#include "includes.hpp"
#include "particule.hpp"
#include "contrainte.hpp"
#include "triangle.hpp"

class Flag {
    public:
        /*
         * Constructeur, qui initialise toutes les variables du drapeau,
         * et qui crée toutes les particules du drapeau ainsi que leurs
         * maillages et contraintes.
         * Et applique à certaines particules du drapeau la statue de "static".
        */
        Flag(float width, float height, int particuleWidth, int particuleHeight, float weight, float damping, glm::mat4 transform);
        
        /*
         * Destructeur.
        */
        virtual ~Flag();
        
        /*
         * Chargement d'une texture.
        */
        void loadTexture(char *filename);
        
        /*
         * Affiche le drapeau.
        */
        void display(GLenum mode);

        /*
         * Affiche le drapeau en fonction des contraintes.
        */
        void displayContraintes();
        
        /*
         * Permet d'appliquer les contraintes, la gravité ainsi que la force au drapeau.
        */
        void step(float timeStep);
        
        std::vector<Particule> particules;

    private:
        std::vector<Contrainte> contraintes;
        std::vector<Triangle> triangles;
        int particuleWidth;
        int particuleHeight;
        bool isTextured;
        GLuint textureID;
};

#endif /* FLAG_H_ */
