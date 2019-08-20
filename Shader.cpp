#include "Shader.h"


Shader::Shader(std::string vsFile, std::string fsFile, std::string gsFile): programID(0), loadFailed(false)
{
	programID = glCreateProgram();
	objects[SHADER_VERTEX] = generateShaders(vsFile, GL_VERTEX_SHADER);
	objects[SHADER_FRAGMENT] = generateShaders(fsFile, GL_FRAGMENT_SHADER);
	objects[SHADER_GEOMETRY] = 0;

	if (!gsFile.empty())
	{
		objects[SHADER_GEOMETRY] = generateShaders(gsFile, GL_GEOMETRY_SHADER);
		glAttachShader(programID, objects[SHADER_GEOMETRY]);
	}

	glAttachShader(programID, objects[SHADER_VERTEX]);
	glAttachShader(programID, objects[SHADER_FRAGMENT]);
	
	//link the program: must do before using the shader
	LinkProgram();

}

bool Shader::LinkProgram()
{
	if (loadFailed)
		return false;

	glLinkProgram(programID);

	GLint code;
	glGetProgramiv(programID, GL_LINK_STATUS, &code);

	return code == GL_TRUE ? true : false;
}

Shader::~Shader()
{
	for (int i = 0; i < 3; i++)
	{
		glDetachShader(programID, objects[i]);
		glDeleteShader(objects[i]);
	}
	glDeleteProgram(programID);
}

GLuint Shader::getProgramId()
{
	return programID;
}

void Shader::Bind()
{
	glUseProgram(programID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

GLuint Shader::generateShaders(std::string sourceFile, GLenum shaderType)
{
	std::string load;
	if (!LoadShaderFile(sourceFile, load))
	{
		std::cout << "Compiling failed!" << std::endl;
		loadFailed = true;
		return 0;
	}

	GLuint shader = glCreateShader(shaderType);

	const char* chars = load.c_str();
	glShaderSource(shader, 1, &chars, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cerr << "Compiling failed!" << std::endl;
		char error[512];
		glGetInfoLogARB(shader, sizeof(error), NULL, error);
		std::cerr << error << std::endl;
		loadFailed = true;
		return 0;
	}

	std::cout << "Compiling success!" << std::endl << std::endl;
	loadFailed = false;

	return shader;
}

bool Shader::LoadShaderFile(std::string from, std::string & into)
{
	std::ifstream file;
	std::string temp;

	std::cout << "Loading shader text from" << from << std::endl << std::endl;

	file.open(from);
	if (!file.is_open())
	{
		std::cerr << "File does not exist!" << std::endl;
		return false;
	}

	while (!file.eof())
	{
		std::getline(file, temp);
		into += temp + "\n";
	}

	file.close();
	//std::cout << into << std::endl << std::endl;
	std::cout << "Loaded Shader text!" << std::endl << std::endl;

	return true;
}

void Shader::setTextureVariable(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}
