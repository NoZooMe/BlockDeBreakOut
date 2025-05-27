#pragma once
#include "include/glad/glad.h"
#include <string>
class ShaderUtils
{
public:
	static std::string LoadShader(const std::string& path);
	static GLuint CompileShader(GLenum type, const std::string& source);
	static GLuint CreateShaderProgram(const std::string& vertPath, const std::string& fragPath);

	~ShaderUtils() = delete;
};

