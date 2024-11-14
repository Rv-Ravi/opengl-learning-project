#include "../Headers/ShaderProgram.h"

ShaderProgram::ShaderProgram()
	:m_programId(glCreateProgram())
{
}

ShaderProgram::ShaderProgram(const std::string& vsPath, const std::string& fsPath)
	:m_programId(glCreateProgram())
{
	getProgram(vsPath, GL_VERTEX_SHADER);
	getProgram(fsPath, GL_FRAGMENT_SHADER);
	processProgram();
}

ShaderProgram::~ShaderProgram()
{
	clear();
}

void ShaderProgram::clear()
{
	if (m_programId != 0)
	{
		glDeleteProgram(m_programId);
		m_programId = 0;
	}
}

void ShaderProgram::getProgram(const std::string& path , GLenum shaderType)
{
	std::ifstream file(path, std::ios::in);

	if (file.is_open())
	{
		std::string line;
		std::stringstream code;
		while (std::getline(file, line))
		{
			if (line != "\n" || line != "")
			{
				code << line << "\n";
			}
		}

		processShader(code.str().c_str(), shaderType);
	}

	file.close();
}

void ShaderProgram::processShader(const char* code, GLenum shaderType)
{

	uint32_t shaderId = glCreateShader(shaderType);
	int32_t codeSize = std::strlen(code);
	glShaderSource(shaderId, 1, &code, &codeSize);
	glCompileShader(shaderId);

	int32_t compileFlg;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileFlg);
	if (!compileFlg)
	{
		int32_t logLen;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLen);
		char* logs = new char[logLen + 1];
		glGetShaderInfoLog(shaderId, logLen,nullptr , logs);
		std::cerr << logs << std::endl;

		delete[] logs;
	}

	glAttachShader(m_programId, shaderId);
	glDeleteShader(shaderId);
}

void ShaderProgram::processProgram()
{
	glLinkProgram(m_programId);
	glValidateProgram(m_programId);

	int32_t valFlg, linkFlg;
	glGetProgramiv(m_programId, GL_VALIDATE_STATUS, &valFlg);
	glGetProgramiv(m_programId, GL_LINK_STATUS, &linkFlg);

	if (!linkFlg || !valFlg)
	{
		int32_t infoLogLen;
		glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &infoLogLen);
		char* programInfo = new char[infoLogLen + 1];
		glGetProgramInfoLog(m_programId, infoLogLen, nullptr, programInfo);
		std::cerr << "The error in : " << (!linkFlg && !valFlg ? "Link and Validate : " : (!linkFlg) ? "Link : "
			: "Validate : ") << programInfo << std::endl;

		delete[] programInfo;
	}

}

void ShaderProgram::bindProgram()
{
	glUseProgram(m_programId);
}

void ShaderProgram::unbindProgram()
{
	glUseProgram(0);
}
