#ifndef TEST_CUBE_H
#define TEST_CUBE_H
#include "CommonHeader.h"

class Shader;
class STLreader;


class TestCube
{
public:
	TestCube();
	~TestCube();

	//debug
	GLuint getVBO();
	GLuint getVAO();

	//rendering purpose
	void loadData();
	void render();

private:
	GLuint VBO, VAO;
	std::vector<Vector3f> vertices;
	int numVertices;

	//triangle vertices;
	void initVertexData();

	//create a shader for the current object from source file
	Shader* objectShader;

	//read from stl file
	STLreader* stlFileReader;
};

#endif

