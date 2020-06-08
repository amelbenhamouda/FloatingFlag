//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#ifndef SKYBOX
#define SKYBOX

#include <iostream>
#include <GL/glew.h>
#include "shader.hpp"
#include "contrainte.hpp"
#include "stb_image.h"

class SkyBox {
    public :
        /*
         * Constructeur de la skybox en fonction du nombre de vertex et des vertices de la skybox.
         */
        SkyBox(const GLsizei count_vertex_skybox, const ShapeVertex *verticesSkybox);

        /*
         * Destructeur
         */
        ~SkyBox();

        /*
         * Creation de la skybox, en fonction du nombre de vertex et des vertices de la skybox.
         */
        void buildSkyBox(const GLsizei count_vertex_skybox, const ShapeVertex *verticesSkybox);

        /*
         * Chargement de la cubemap à l'aide d'un vecteur contenant les faces de la skybox.
         */
        unsigned int loadCubemap(std::vector<std::string> faces);

        /*
         * Permet l'activation et l'affichage de la skybox, en fonction :
         *      -> du programme de la skybox qui permet le chargement des textures,
         *      -> de l'identifiant de la texture souhaitée,
         *      -> de la distance de rendu,
         *      -> du ratio en fonction de la taille de la fenetre,
         *      -> et de la view matrice.
         */
        void activeSkyBox( Shader *skytext, const GLuint &cubemapTexture, float distRendu, float ratio_h_w, glm::mat4 VMatrix);

    private :
        GLuint vbo;
        GLuint vao;
};

#endif // SKYBOX