//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../include/flag.hpp"

Flag::Flag(float width, float height, int particuleWidth, int particuleHeight, float weight, float damping, glm::mat4 transform) {
    this->particuleWidth = particuleWidth;
    this->particuleHeight = particuleHeight;
    this->isTextured = true;
    this->textureID = 0;

    float particuleSeperationX = width / particuleWidth;
    float particuleSeperationY = height / particuleHeight;
    float numParticules = particuleWidth * particuleHeight;
    float particuleMass = numParticules / weight;
    float particuleDamping = 1 - damping;

    // Creation des particules
    for (int y = 0; y < particuleHeight; y++) {
        for (int x = 0; x < particuleWidth; x++) {
            particules.push_back(Particule(
                    glm::vec3(transform * glm::vec4(x * particuleSeperationX, -y * particuleSeperationY, 0, 1)),
                    particuleMass, particuleDamping,
                    glm::vec2((float)x / (particuleWidth - 1), -(float)y / (particuleHeight - 1))
            ));
        }
    }

    // Creation des triangles pour le maillage
    for (int y = 1; y < particuleHeight; y++) {
        for (int x = 1; x < particuleWidth; x++) {
            Particule *p1 = &particules[(y - 1) * particuleWidth + x - 1];
            Particule *p2 = &particules[(y - 1) * particuleWidth + x];
            Particule *p3 = &particules[y * particuleWidth + x - 1];
            Particule *p4 = &particules[y * particuleWidth + x];

            // p1 - p2
            //  | / |
            // p3 - p4
            triangles.push_back(Triangle(p3, p1, p2));
            triangles.push_back(Triangle(p2, p4, p3));

            // p1 - p2
            //  | \ |
            // p3 - p4
            triangles.push_back(Triangle(p4, p3, p1));
            triangles.push_back(Triangle(p4, p2, p1));
        }
    }

    // Definissions des contraintes entre particule
    for (int i = 0; i < numParticules; i++) {
        bool leftCol = i % particuleWidth == 0;
        bool rightCol = (i + 1) % particuleWidth == 0;
        bool topRow = i < particuleWidth;
        bool topRows = i < particuleWidth * 2; //top 2 rows
        bool leftCols = leftCol || (i - 1) % particuleWidth == 0; //2 leftmost columns

        //vertical (up)
        if (!topRow) {
            contraintes.push_back(Contrainte(&particules[i], &particules[i - particuleWidth]));
        }
        if (!topRows) {
            contraintes.push_back(Contrainte(&particules[i], &particules[i - (particuleWidth * 2)]));
        }
        //horizontal (left)
        if (!leftCol) {
            contraintes.push_back(Contrainte(&particules[i], &particules[i - 1]));
        }
        if (!leftCols) {
            contraintes.push_back(Contrainte(&particules[i], &particules[i - 2]));
        }
        //diagonal \  .
        if (!topRow && !leftCol) {
            contraintes.push_back(Contrainte(&particules[i], &particules[i - 1 - particuleWidth]));
        }
        //diagonal /  .
        if (!topRow && !rightCol) {
            contraintes.push_back(Contrainte(&particules[i], &particules[i + 1 - particuleWidth]));
        }
    }

    // donner au drapeau une petite poussée dans la direction z
    particules[numParticules / 2 + particuleWidth / 2].force.z -= 1;

    // Rendre certains points statiques
    // particules[particuleWidth/2].isStatic = true; // en haut au milieu
    // particules[numParticules-particuleHeight].isStatic = true; // en bas au milieu
    // particules[0].isStatic = true; // en haut à gauche
    // particules[particuleWidth-1].isStatic = true; // en haut à droite
    // particules[numParticules-particuleWidth].isStatic = true; // en bas à gauche
    // particules[numParticules-1].isStatic = true; //en bas à droite
    for (int i = 0; i < particuleHeight; i++) { // Bord gauche
        particules[i*particuleWidth].isStatic = true;
    }
}

Flag::~Flag() {}

//mode: GL_TRIANGLES pour solid && GL_LINE_LOOP pour wireframe
void Flag::display(GLenum mode) {
    //Bind la texture
    if (isTextured) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    //Calcul des normales
    for (int y = 0; y < particuleHeight; y++) {
        for (int x = 0; x < particuleWidth; x++) {
            glm::vec3 vy, vx;
            Particule *p = &particules[y * particuleWidth + x];

            if (y > 0) {
                vy = particules[(y - 1) * particuleWidth + x].pos;
            }
            else {
                vy = p->pos;
            }

            if (y < particuleHeight) {
                vy -= particules[(particuleHeight - 1) * particuleWidth + x].pos;
            }
            else {
                vy -= p->pos;
            }

            if (x > 0) {
                vx = particules[y * particuleWidth + x - 1].pos;
            }
            else {
                vx = p->pos;
            }

            if (x < particuleWidth - 1) {
                vx -= particules[y * particuleWidth + x + 1].pos;
            }
            else {
                vx -= p->pos;
            }
            p->normal = glm::normalize(glm::cross(vy, vx));
        }
    }
    // Dessin du drapeau
    glBegin(mode);
    for (std::vector<Triangle>::size_type i = 0; i < triangles.size(); i++) {
        triangles[i].display();
    }
    glEnd();
    // Dé-bind la texture
    if (isTextured) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Flag::displayContraintes() {
    for (std::vector<Contrainte>::size_type i = 0; i < contraintes.size(); i++) {
        contraintes[i].display();
    }
}

void Flag::step(float timeStep) {
    //Gravite
    for (std::vector<Particule>::size_type i = 0; i < particules.size(); i++) {
        particules[i].force += glm::vec3(0, -0.3, 0) * timeStep;
    }
    // Satisfaire les contraintes
    for (int n = 0; n < 20; n++) {
        for (std::vector<Contrainte>::size_type i = 0; i < contraintes.size(); i++) {
            contraintes[i].satisfy();
        }
    }
    // Appliquer des forces
    for (std::vector<Particule>::size_type i = 0; i < particules.size(); i++) {
        particules[i].step(timeStep);
    }
}

void Flag::loadTexture(char* filename) {
    GLenum texture = GL_TEXTURE0;
    GLenum target = GL_TEXTURE_2D;

    // Initiez le stockage de texture et définissez certains paramètres.
    glActiveTexture(texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &textureID);
    glBindTexture(target, textureID);

    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //Charger le fichier png à partir du disque et le décoder
    int imageWidth, imageHeight, comp;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* imageData = stbi_load(filename, &imageWidth, &imageHeight, &comp, STBI_rgb);
    // Charger la texture dans GL
    glTexImage2D(target, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    isTextured = true;
}
