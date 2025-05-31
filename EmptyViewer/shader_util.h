#pragma once
// shader_util.h
#pragma once
#include <glad/glad.h>
#include <string>

// 파일 내용을 문자열로 읽어오는 함수
std::string LoadFileToString(const char* filepath);

// 쉐이더 소스를 컴파일하는 함수
GLuint CompileShader(GLenum type, const char* source);

// 쉐이더 프로그램을 생성하는 함수 (파일 경로 기반)
GLuint CreateShaderProgram(const char* vertexPath, const char* fragmentPath);
