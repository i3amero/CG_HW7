// main_Phong_Shader.cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include "sphere_scene.cpp"
#include "shader_util.h"

int Width = 800;
int Height = 600;

GLuint VAO, VBO, NBO, EBO;
GLuint shaderProgram;

void setupBuffers() {
    create_scene();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &NBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * gNumVertices * 3, gVertexBuffer, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // Normal buffer
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * gNumVertices * 3, gNormalBuffer, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * gNumTriangles * 3, gIndexBuffer, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void render() {
    GLint curProg = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &curProg);
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);

    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.02, 0.02, 0.02));

    glm::mat4 model = translation * scale;
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)Width / Height, 0.1f, 100.0f);

    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uModel"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uView"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uProjection"), 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, "uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

    glUniform3f(glGetUniformLocation(shaderProgram, "uViewPos"), 0, 0, -10);
    glUniform3f(glGetUniformLocation(shaderProgram, "uLightPos"), -32.0f, 100.0f, -100.0f);
    glUniform3f(glGetUniformLocation(shaderProgram, "uLightColor"), 1.0f, 1.0f, 1.0f);

    glUniform3f(glGetUniformLocation(shaderProgram, "uKa"), 0.0f, 1.0f, 0.0f);
    glUniform3f(glGetUniformLocation(shaderProgram, "uKd"), 0.0f, 0.5f, 0.0f);
    glUniform3f(glGetUniformLocation(shaderProgram, "uKs"), 0.8f, 0.8f, 0.8f);
    glUniform1f(glGetUniformLocation(shaderProgram, "uShininess"), 32.0f);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, gNumTriangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(Width, Height, "HW7 - Phong Shader", NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);

    shaderProgram = CreateShaderProgram("Phong.vert", "Phong.frag");
    setupBuffers();

    while (!glfwWindowShouldClose(window)) {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
