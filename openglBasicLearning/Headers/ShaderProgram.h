#pragma once

#include "glad/glad.h"
#include <string>

#include <fstream>
#include <sstream>
#include <iostream>

class ShaderProgram
{
private:
	uint32_t m_programId;

public:
	ShaderProgram();
	ShaderProgram(const std::string& vsPath, const std::string& fsPath);

	~ShaderProgram();

	void clear();

	void getProgram(const std::string& path, GLenum shaderType);

	void processShader(const char* code, GLenum shaderType);

	void processProgram();

	void bindProgram();

	void unbindProgram();

};

