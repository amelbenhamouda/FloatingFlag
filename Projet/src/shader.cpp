//============================================================================
// Author      : BEN HAMOUDA Amel
//============================================================================

#include "../include/shader.hpp"

char *textFileRead(char *fn) {
    FILE *fp;
    char *content = NULL;
    int count = 0;
    if (fn != NULL) {
        fp = fopen(fn,"rt");
        if (fp != NULL) {
            fseek(fp, 0, SEEK_END);
            count = ftell(fp);
            rewind(fp);
            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count + 1));
                count = fread(content, sizeof(char), count, fp);
                content[count] = '\0';
            }
            fclose(fp);
        }
    }
    return content;
}

Shader::Shader(char* vertSource, char* fragSource, char* type) {
    char *vs = NULL, *fs = NULL;
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    // lecture des fichiers shader
    vs = textFileRead(vertSource);
    fs = textFileRead(fragSource);
    // attacher du code au shader
    const char *ff = fs;
    const char *vv = vs;
    glShaderSource(vertShader, 1, &vv,NULL);
    glShaderSource(fragShader, 1, &ff,NULL);
    // après que les fichiers ont été chargés par GL, 
    // nous n'en avons pas besoin
    free(vs); 
    free(fs);
    // compile
    glCompileShader(vertShader);
    glCompileShader(fragShader);

    program = glCreateProgram();
    // attacher le shader au programme
    glAttachShader(program, fragShader);
    glAttachShader(program, vertShader);
    // lier le programme
    glLinkProgram(program);
    if (strcmp(type, "skybox") == 0) { //chaine egale
        // obtenir les index des variables uniformes dans les shaders 
        // pour une utilisation ultérieure
        uCubeMap = glGetUniformLocation(program, "uCubeMap");
        uMVP = glGetUniformLocation(program, "uMVP");
    }
    else {
        // obtenir les index des variables uniformes dans les shaders 
        // pour une utilisation ultérieure
        ModelLocation = glGetUniformLocation(program, "Model");
        ViewLocation = glGetUniformLocation(program, "View");
        ProjectionLocation = glGetUniformLocation(program, "Projection");
        // obtenir les index des attributs de sommet dans les shaders 
        // pour une utilisation ultérieure
        VertexLocation = glGetAttribLocation(program, "Vertex");
        NormalLocation = glGetAttribLocation(program, "Normal");
    }
}

void Shader::setModelMatrix(glm::mat4 m) {
    glUseProgram(program);
    glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setViewMatrix(glm::mat4 m) {
    glUseProgram(program);
    glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setProjectionMatrix(glm::mat4 m) {
    glUseProgram(program);
    glUniformMatrix4fv(ProjectionLocation, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::use() {
    glUseProgram(program);
}

Shader::~Shader() {
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    glDeleteProgram(program);
}
