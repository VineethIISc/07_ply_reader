#ifndef PLY_MODEL_H
#define PLY_MODEL_H

class Shader;
class PLYreader;

class TestPlyModel
{
public:
	TestPlyModel();
	~TestPlyModel();

	//debug
	GLuint getVBO();
	GLuint getVAO();

	//rendering purpose
	void loadData();
	void render();

private:
	GLuint VBO, VAO;
	//store vertices and indices
	std::vector<Vector3f> vertices;
	std::vector<Vector3ui> indices;
	int numVertices, numIndices;
	GLuint indexBufferOffset;

	//triangle vertices;
	void initData();

	//create a shader for the current object from source file
	Shader* objectShader;

	//read from stl file
	PLYreader* plyreader;;
};
#endif

