#pragma once
// shader_util.h
#pragma once
#include <glad/glad.h>
#include <string>

// ���� ������ ���ڿ��� �о���� �Լ�
std::string LoadFileToString(const char* filepath);

// ���̴� �ҽ��� �������ϴ� �Լ�
GLuint CompileShader(GLenum type, const char* source);

// ���̴� ���α׷��� �����ϴ� �Լ� (���� ��� ���)
GLuint CreateShaderProgram(const char* vertexPath, const char* fragmentPath);
