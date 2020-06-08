//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#include "../include/cube.hpp"

Cube::Cube(glm::vec3 position, float size, glm::vec4 color) {
    this->pos = position;
    this->size = size;
    this->color = color;
}

Cube::~Cube() {}

void Cube::display(Shader *shader) {
    shader->setModelMatrix(glm::translate(pos));
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidCube(size);
}

void Cube::build(GLfloat size_c) {
    std::vector<ShapeVertex> data;
    // Construit l'ensemble des vertex
    ShapeVertex vertex;

    /// FACE 1 - face
    // triangle 1
    // 1
    vertex.texCoords = glm::vec2(0, 1);
    vertex.normal = glm::vec3(0, 0, 1);
    vertex.position = glm::vec3(0,0,0);
    data.push_back(vertex);
    // 2
    vertex.texCoords = glm::vec2(1, 1);
    vertex.normal = glm::vec3(0, 0, 1);
    vertex.position = glm::vec3(size_c,0,0);
    data.push_back(vertex);
    // 3
    vertex.texCoords = glm::vec2(0, 0);
    vertex.normal = glm::vec3(0, 0, 1);
    vertex.position = glm::vec3(0,size_c,0);;
    data.push_back(vertex);
    // triangle 2
    // 1
    vertex.texCoords = glm::vec2(0, 0);
    vertex.normal = glm::vec3(0, 0, 1);
    vertex.position = glm::vec3(0,size_c,0);;
    data.push_back(vertex);
    // 2
    vertex.texCoords = glm::vec2(1, 1);
    vertex.normal = glm::vec3(0, 0, 1);
    vertex.position = glm::vec3(size_c,0,0);
    data.push_back(vertex);
    // 3
    vertex.texCoords = glm::vec2(1, 0);
    vertex.normal = glm::vec3(0, 0, 1);
    vertex.position = glm::vec3(size_c,size_c,0);;
    data.push_back(vertex);

    ///FACE 2 - dos
    // triangle 3
    // 1
    vertex.texCoords = glm::vec2(0, 1);
    vertex.normal = glm::vec3(0, 0, -1);
    vertex.position = glm::vec3(0,0,-size_c);
    data.push_back(vertex);
    // 2
    vertex.texCoords = glm::vec2(0, 0);
    vertex.normal = glm::vec3(0, 0, -1);
    vertex.position = glm::vec3(0,size_c,-size_c);;
    data.push_back(vertex);
    // 3
    vertex.texCoords = glm::vec2(1, 1);
    vertex.normal = glm::vec3(0, 0, -1);
    vertex.position = glm::vec3(size_c,0,-size_c);
    data.push_back(vertex);
    // triangle 4
    // 1
    vertex.texCoords = glm::vec2(0, 0);
    vertex.normal = glm::vec3(0, 0, -1);
    vertex.position = glm::vec3(0,size_c,-size_c);;
    data.push_back(vertex);
    //2
    vertex.texCoords = glm::vec2(1, 0);
    vertex.normal = glm::vec3(0, 0, -1);
    vertex.position = glm::vec3(size_c,size_c,-size_c);;
    data.push_back(vertex);
    //3
    vertex.texCoords = glm::vec2(1, 1);
    vertex.normal = glm::vec3(0, 0, -1);
    vertex.position = glm::vec3(size_c,0,-size_c);
    data.push_back(vertex);

    /// FACE 3 - droite
    // triangle 5
    // 1
    vertex.texCoords = glm::vec2(0, 1);
    vertex.normal = glm::vec3(1, 0, 0);
    vertex.position = glm::vec3(size_c,0,0);
    data.push_back(vertex);
    // 2
    vertex.texCoords = glm::vec2(1, 1);
    vertex.normal = glm::vec3(1, 0, 0);
    vertex.position = glm::vec3(size_c,0,-size_c);
    data.push_back(vertex);
    // 3
    vertex.texCoords = glm::vec2(0, 0);
    vertex.normal = glm::vec3(1, 0, 0);
    vertex.position = glm::vec3(size_c,size_c,0);
    data.push_back(vertex);
    // triangle 6
    // 1
    vertex.texCoords = glm::vec2(0, 0);
    vertex.normal = glm::vec3(1, 0, 0);
    vertex.position = glm::vec3(size_c,size_c,0);
    data.push_back(vertex);
    // 2
    vertex.texCoords = glm::vec2(1, 1);
    vertex.normal = glm::vec3(1, 0, 0);
    vertex.position = glm::vec3(size_c,0,-size_c);
    data.push_back(vertex);
    // 3
    vertex.texCoords = glm::vec2(1, 0);
    vertex.normal = glm::vec3(1, 0, 0);
    vertex.position = glm::vec3(size_c,size_c,-size_c);
    data.push_back(vertex);

    /// Face 4 - gauche
    // triangle 7
    // 1
    vertex.texCoords = glm::vec2(0, 1);
    vertex.normal = glm::vec3(-1, 0, 0);
    vertex.position = glm::vec3(0,0,-size_c);
    data.push_back(vertex);
    // 2
    vertex.texCoords = glm::vec2(1, 1);
    vertex.normal = glm::vec3(-1, 0, 0);
    vertex.position = glm::vec3(0,0,0);
    data.push_back(vertex);
    // 3
    vertex.texCoords = glm::vec2(0, 0);
    vertex.normal = glm::vec3(-1, 0, 0);
    vertex.position = glm::vec3(0,size_c,-size_c);
    data.push_back(vertex);
    // triangle 8
    // 1
    vertex.texCoords = glm::vec2(0, 0);
    vertex.normal = glm::vec3(-1, 0, 0);
    vertex.position = glm::vec3(0,size_c,-size_c);
    data.push_back(vertex);
    // 2
    vertex.texCoords = glm::vec2(1, 1);
    vertex.normal = glm::vec3(-1, 0, 0);
    vertex.position = glm::vec3(0,0,0);
    data.push_back(vertex);
    // 3
    vertex.texCoords = glm::vec2(1, 0);
    vertex.normal = glm::vec3(-1, 0, 0);
    vertex.position = glm::vec3(0,size_c,0);
    data.push_back(vertex);

    /// Face 5 - haut
    // triangle 9
    // 1
    vertex.texCoords = glm::vec2(0, 1);
    vertex.normal = glm::vec3(0, 1, 0);
    vertex.position = glm::vec3(size_c,size_c,0);
    data.push_back(vertex);
    // 2
    vertex.texCoords = glm::vec2(1, 1);
    vertex.normal = glm::vec3(0, 1, 0);
    vertex.position = glm::vec3(size_c,size_c,-size_c);
    data.push_back(vertex);
    // 3
    vertex.texCoords = glm::vec2(0, 0);
    vertex.normal = glm::vec3(0, 1, 0);
    vertex.position = glm::vec3(0,size_c,0);
    data.push_back(vertex);
    // triangle 10
    // 1
    vertex.texCoords = glm::vec2(0, 0);
    vertex.normal = glm::vec3(0, 1, 0);
    vertex.position = glm::vec3(0,size_c,0);
    data.push_back(vertex);
    // 2
    vertex.texCoords = glm::vec2(1, 1);
    vertex.normal = glm::vec3(0, 1, 0);
    vertex.position = glm::vec3(size_c,size_c,-size_c);
    data.push_back(vertex);
    // 3
    vertex.texCoords = glm::vec2(1, 0);
    vertex.normal = glm::vec3(0, 1, 0);
    vertex.position = glm::vec3(0,size_c,-size_c);
    data.push_back(vertex);

    ///  Face 6 - bas
    // triangle 11
    // 1
    vertex.texCoords = glm::vec2(0, 1);
    vertex.normal = glm::vec3(0, -1, 0);
    vertex.position = glm::vec3(0,0,-size_c);
    data.push_back(vertex);
    // 2
    vertex.texCoords = glm::vec2(1, 1);
    vertex.normal = glm::vec3(0, -1, 0);
    vertex.position = glm::vec3(size_c,0,-size_c);
    data.push_back(vertex);
    // 3
    vertex.texCoords = glm::vec2(0, 0);
    vertex.normal = glm::vec3(0, -1, 0);
    vertex.position = glm::vec3(0,0,0);
    data.push_back(vertex);
    // triangle 12
    // 1
    vertex.texCoords = glm::vec2(0, 0);
    vertex.normal = glm::vec3(0, -1, 0);
    vertex.position = glm::vec3(0,0,0);
    data.push_back(vertex);
    // 2
    vertex.texCoords = glm::vec2(1, 1);
    vertex.normal = glm::vec3(0, -1, 0);
    vertex.position = glm::vec3(size_c,0,-size_c);
    data.push_back(vertex);
    // 3
    vertex.texCoords = glm::vec2(1, 0);
    vertex.normal = glm::vec3(0, -1, 0);
    vertex.position = glm::vec3(size_c,0,0);
    data.push_back(vertex);

    m_nVertexCount = 36;
    m_Vertices = data;
}