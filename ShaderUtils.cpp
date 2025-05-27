#include "ShaderUtils.h"
#include <fstream>
#include <sstream>

std::string ShaderUtils::LoadShader(const std::string& path) {
	std::ifstream file(path);
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint ShaderUtils::CompileShader(GLenum type, const std::string& source) {
	GLuint shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);
	return shader;
}

GLuint ShaderUtils::CreateShaderProgram(const std::string& vertPath, const std::string& fragPath) {
	GLuint vs = CompileShader(GL_VERTEX_SHADER, LoadShader(vertPath));
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, LoadShader(fragPath));
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	return program;
}