//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#ifndef SHADER_H_
#define SHADER_H_

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
    public:
        GLuint vertShader, fragShader;
        GLuint program;
        GLuint ModelLocation, ViewLocation, ProjectionLocation;
        GLuint VertexLocation, NormalLocation;
        GLuint uCubeMap, uMVP;

        /*
         * Mise à jour de la ModelMatrix.
        */
        void setModelMatrix(glm::mat4);

        /*
         * Mise à jour de la ViewMatrix.
        */
        void setViewMatrix(glm::mat4);

        /*
         * Mise à jour de la matrice de projection.
        */
        void setProjectionMatrix(glm::mat4);

        /*
         * Constructeur : qui charge les shaders et initialise les variables.
        */
        Shader(char* vertSource, char* fragSource, char* type);

        /*
         * Destructeur.
        */
        virtual ~Shader();

        /*
         * Fonction qui "lance" les shaders.
        */
        void use();
};

#endif /* SHADER_H_ */
