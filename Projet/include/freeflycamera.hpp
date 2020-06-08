//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#pragma once

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

class FreeflyCamera {
    public:

        /*
         * Destructeur.
        */
        virtual  ~FreeflyCamera(){};

        /*
         * Constructeur : initialise les paramètres de la caméra.
        */
        FreeflyCamera(): m_Position(-52, 600, -2.979e-05), m_fPhi(0), m_fTheta(-M_PI_2) {
            computeDirectionVectors();
        };

        /*
         * Déplacement à gauche.
        */
        void moveLeft(float t) {
            m_Position += t * m_LeftVector;
        }

        /*
         * Déplacement vers l'avant.
        */
        void moveFront(float t) {
            m_Position += t * m_FrontVector;
        }

        /*
         * Renvoie la ViewMatrix.
        */
        glm::mat4 getViewMatrix() const {
            return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
            // eye // Le point de vue V (argument point) // Le dernier argument est l'axe vertical de la caméra
        }

        /*
         * Renvoie le FrontVector.
        */
        glm::vec3 getFrontVector() const { 
            return m_FrontVector;
        }

        /*
         * Renvoie la position.
        */
        glm::vec3 getPosition() const {
            return m_Position;
        }

        /*
         * Modifie la position.
        */
        void setPosition(glm::vec3 pos) { 
            m_Position = pos;
        }

    private:
        glm::vec3 m_Position;
        float m_fPhi;
        float m_fTheta;
        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;

        /*
         * Calcul les directions des différents vecteurs de la caméra.
        */
        void computeDirectionVectors() {
            m_FrontVector[0] = cos(m_fTheta) * sin(m_fPhi); //F⃗ =(cos(θ)sin(ϕ), sin(θ), cos(θ)cos(ϕ))
            m_FrontVector[1] = sin(m_fTheta);
            m_FrontVector[2] = cos(m_fTheta) * cos(m_fPhi);

            m_LeftVector[0] = sin(m_fPhi + M_PI / 2); //L⃗ =(sin(ϕ+π/2), 0, cos(ϕ+π/2))
            m_LeftVector[1] = 0;
            m_LeftVector[2] = cos(m_fPhi + M_PI / 2);

            m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
        }
};
