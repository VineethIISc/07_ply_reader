#ifndef SHADER_H
#define SHADER_H

#include "CommonHeader.h"

#define SHADER_VERTEX 0
#define SHADER_FRAGMENT 1
#define SHADER_GEOMETRY 2

class Shader
{
public:
	Shader(std::string vertex, std::string fragment, std::string geometry = "");	
	~Shader();

	//shader program id
	GLuint getProgramId();
	   
	//bind and unbind shader program
	void Bind();
	void Unbind();

	//assign texture variable 
	void setTextureVariable(const std::string& name, int value);

private:
	GLuint objects[3];
	GLuint programID;
	bool loadFailed;

	//generateShaders from the source file
	GLuint generateShaders(std::string, GLenum shaderType);

	//link the shader program
	bool LinkProgram();

	//load shader from file
	bool LoadShaderFile(std::string from, std::string & into);
};
#endif

