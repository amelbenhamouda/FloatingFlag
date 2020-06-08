//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#include "../include/includes.hpp"
#include "../include/shader.hpp"
#include "../include/flag.hpp"
#include "../include/sphere.hpp"
#include "../include/freeflycamera.hpp"
#include "../include/cube.hpp"
#include "../include/skybox.hpp"

#define M_PI 3.14159265358979323846
#define NbCubes 88

GLuint mainWnd;
GLuint winWidth = 640;
GLuint winHeight = 480;
float ratio_h_w = (float)winWidth / (float)winHeight;
GLuint timeStep = 1000 / 60;
GLuint texFond;

Shader *shader, *skytex;
Flag *flag;
Sphere *sphere;
Cube *cubes[NbCubes];
FreeflyCamera camera;
SkyBox *skybox;

/*
 *
*/
void timer(int t) {
    flag->step(timeStep);
    sphere->collision(&(flag->particules));
    glutPostRedisplay();
    glutTimerFunc(timeStep, timer, t);
}

/*
 * Permet de changer la taille de la fenetre.
*/
void reshape(int w, int h) {
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
}

/*
 * Permet de connaitre la direction que doit prendre la caméra selon les touches du clavier.
*/
void processInput(int key, int x, int y) {
    float deltaTime = 0.5f;
    if (key == GLUT_KEY_DOWN) { // fleche bas
        camera.moveFront(-deltaTime);
    }
    if (key == GLUT_KEY_UP) { // fleche haut
        camera.moveFront(deltaTime);
    }
    if (key == GLUT_KEY_LEFT) { // fleche gauche
        camera.moveLeft(deltaTime);
    }
    if (key == GLUT_KEY_RIGHT) { // fleche droite
        camera.moveLeft(-deltaTime);
    }
}

/*
 * Mise à jour de la caméra.
*/
void setCamera() {
    //projection matrix
    glm::mat4 projection = glm::perspective((float)(20 * M_PI / 180), (float)winWidth / (float)winHeight, 1.f, 1000.f);
    shader->setProjectionMatrix(projection);
    //view matrix
    glm::mat4 view = camera.getViewMatrix();
    shader->setViewMatrix(view);
}

/*
 * Mise à jour de la lumiére.
*/
void setLight() {
    float direction[] = { 0.5f, 1.0f, 1.0f, 0.0f };
    float diffintensity[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    float ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, direction);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffintensity);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glEnable(GL_LIGHT0);
}

/*
 * Netoyage de la fenetre.
*/
void reset() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    skybox->activeSkyBox(skytex, texFond, 5000.0f, ratio_h_w, camera.getViewMatrix());
}

/*
 * Affiche le drapeau, le porte drapeau et permet le mouvement de la caméra et de la lumiére.
*/
void display() {
    reset();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("%s\n", gluErrorString(err));
    }

    setCamera();
    setLight();
    shader->setModelMatrix(glm::mat4());
    glColor3f(1.0f, 1.0f, 1.0f);
    if (flag != NULL){
        flag->display(GL_TRIANGLES);
        //flag->displayContraintes(); // avec les mailles
    }
    
    sphere->display(shader);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);

    // Porte drapeau
    for (int i = 0; i < NbCubes; i++) {
        cubes[i]->display(shader);
    }

    glutSwapBuffers();
}

/*
 * Permet le déplacement de la sphère, pour illustrer le vent.
*/
void keyboardHandler(unsigned char key, int x, int y) {
    if (key == 'z') { // Haut
        sphere->move(glm::vec3(0, 0, 1));
    }
    if (key == 's') { // Bas
        sphere->move(glm::vec3(0, 0, -1));
    }
    if (key == 'q') { // Gauche
        sphere->move(glm::vec3(1, 0, 0));
    }
    if (key == 'd') { // Droite
        sphere->move(glm::vec3(-1, 0, 0));
    }
    if (key == 'r') { // Profondeur Haut
        sphere->move(glm::vec3(0, 1, 0));
    }
    if (key == 'f') { // Profondeur Bas
        sphere->move(glm::vec3(0, -1, 0));
    }
}

/*
 * Menu qui permet à l'utilisateur de choisir le drapeau qu'il souhaite faire flotté.
*/
char* menu() {
    std::cout << "Choisir quel drapeau vous souhaitez :\n   1. France ,\n   2. Canada,\n   3. Tunisie,\n   4. Nouvelle Zélande,\n   5. Etat-Unis" << std::endl;
    int choice;
    std::cin >> choice;
    while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5){
        std::cout << "Votre choix est incorrecte, veuillez recommencer. "<< std::endl;
        std::cout << "Choisir quel drapeau vous souhaitez :\n   1. France ,\n   2. Canada,\n   3. Tunisie,\n   4. Nouvelle Zélande,\n   5. Etat-Unis" << std::endl;
        std::cin >> choice;
    }

    char* filename;
    if (choice == 1) {
        filename = (char*)"images/france.png";
    } 
    else if (choice == 2) {
        filename = (char*)"images/canada.png";
    }
    else if (choice == 3) {
        filename = (char*)"images/tunisie.png";
    }
    else if (choice == 4) {
        filename = (char*)"images/nzFlag.png";
    }
    else if (choice == 5) {
        filename = (char*)"images/etatUnis.png";
    }
    return filename;
}

/*
 * Fonction principal.
*/
int main(int argc, char** argv) {
    char* filename = menu();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);
    mainWnd = glutCreateWindow("Flag");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
    // Initialisation des shaders pour la skybox
    skytex = new Shader((char*)"shaders/skybox.vs.glsl", (char*)"shaders/skybox.fs.glsl", (char*)"skybox");

    // Initialisation des shaders pour le drapeau
    shader = new Shader((char*)"shaders/phong.vs.glsl", (char*)"shaders/phong.fs.glsl", (char*)"");
    shader->use();

    float size_cube = 1;
    Cube cubeSkybox(size_cube);
    GLsizei count_vertex_skybox = cubeSkybox.getVertexCount();
    const ShapeVertex*  Datapointeur_skybox = cubeSkybox.getDataPointer();
    ShapeVertex verticesSkybox[count_vertex_skybox];
    for (auto i = 0; i < count_vertex_skybox; i++) { // Skybox
        verticesSkybox[i] = *Datapointeur_skybox;
        verticesSkybox[i].position.x -= 0.5;
        verticesSkybox[i].position.y -= 0.5;
        verticesSkybox[i].position.z += 0.5;
        Datapointeur_skybox++;
    }
    skybox = new SkyBox(count_vertex_skybox, verticesSkybox);

    // Texture Skybox
    std::vector<std::string> facesGalaxy { "images/skybox/right.png", "images/skybox/left.png", "images/skybox/top.png", "images/skybox/bottom.png", 
                                           "images/skybox/front.png", "images/skybox/back.png" };
    //Binding de la texture
    texFond = skybox->loadCubemap(facesGalaxy);

    // Initialisation du drapeau
    glm::mat4 translate = glm::translate(glm::vec3(-50, 20, 25)) * glm::rotate(30.f, glm::vec3(1, 0, 0));
    flag = new Flag(100, 50, 100, 50, 100, 0.01, translate);
    flag->loadTexture(filename);

    // Sphere qui permet le mouvement du drapeau
    sphere = new Sphere(glm::vec3(-50, 0, 49), 10, glm::vec4(0.2, 0.8, 0.2, 1));

    // Plusieurs cubes qui permet la création du porte drapeau
    int zCube = 75;
    for (int i = 0; i < NbCubes; i++){
        cubes[i] = new Cube(glm::vec3(-50, 0, zCube), 2, glm::vec4(0.2, 0.8, 0.2, 1));
        zCube -= 2;
    }

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardHandler);
    glutSpecialFunc(processInput);
    
    timer(0); // Pour faire bouger le drapeau

    glutMainLoop();

    return EXIT_SUCCESS;
}
