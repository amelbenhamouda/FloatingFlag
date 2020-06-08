//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#ifndef CUBE_H_
#define CUBE_H_

#include "includes.hpp"
#include "particule.hpp"
#include "shader.hpp"
#include "contrainte.hpp"

class Cube {
    public:
        /*
         * Constructeur: initialise la position, la taille et la couleur du cube.
        */
        Cube(glm::vec3 position, float size, glm::vec4 color);

        /*
         * Destructeur.
        */
        virtual ~Cube();

        /*
         * Affiche le cube à l'aide de GLUT.
        */
        void display(Shader *shader);

        /*
         * Constructeur: alloue le tableau de données et construit les attributs des vertex.
        */
        Cube(GLfloat size_c) : m_nVertexCount(0) {
            build(size_c); // Construction (voir le .cpp)
        }

        /* 
         * Alloue et construit les données (implantation dans le .cpp).
        */
        void build(GLfloat size_c);

        /*
         * Renvoit le pointeur vers les données.
        */
        const ShapeVertex* getDataPointer() const {
            return &m_Vertices[0];
        }

        /*
         * Renvoit le nombre de vertex.
        */
        GLsizei getVertexCount() const {
            return m_nVertexCount;
        }

    private:
        glm::vec4 color;
        float size;
        glm::vec3 pos;
        std::vector<ShapeVertex> m_Vertices;
        GLsizei m_nVertexCount; // Nombre de sommets.
};

#endif /* CUBE_H_ */