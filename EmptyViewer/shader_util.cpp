// shader_util.cpp
#include "shader_util.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string LoadFileToString(const char* filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "파일 열기 실패: " << filepath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint CompileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "셰이더 컴파일 오류:\n" << infoLog << std::endl;
    }
    return shader;
}

GLuint CreateShaderProgram(const char* vertexPath, const char* fragmentPath) {
    std::string vertCode = LoadFileToString(vertexPath);
    std::string fragCode = LoadFileToString(fragmentPath);

    GLuint vertShader = CompileShader(GL_VERTEX_SHADER, vertCode.c_str());
    GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, fragCode.c_str());

    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "셰이더 프로그램 링크 오류:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    return program;
}
