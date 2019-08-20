#include "Shader.h"
#include "PLYreader.h"
#include "TestPlyModel.h"

TestPlyModel::TestPlyModel()
{
	plyreader = new PLYreader(MODEL_PATH"table_b.ply");

	//draw all vertices
	numVertices = plyreader->getNumberOfVertices();
	numIndices = plyreader->getNumberOfIndices();

	//create vertices and indices
	initData();
}


TestPlyModel::~TestPlyModel()
{
	if (VAO)
		glDeleteVertexArrays(1, &VAO);

	if (VBO)
		glDeleteBuffers(1, &VBO);

	if (plyreader)
		delete plyreader;

	if (objectShader)
		delete objectShader;
}

GLuint TestPlyModel::getVBO()
{
	return VBO;
}

GLuint TestPlyModel::getVAO()
{
	return VAO;
}

void TestPlyModel::loadData()
{
	//create vertex array objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind VAO, VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);	//element array buffer for indices

	//allocate memory in GPU
	GLsizeiptr VertexSize = sizeof(Vector3f) * numVertices;
	GLsizeiptr IndexSize = sizeof(unsigned int) * numIndices;
	GLsizeiptr TotalSize = VertexSize + IndexSize;
	glBufferData(GL_ARRAY_BUFFER, TotalSize, NULL, GL_STATIC_DRAW);

	//pass vertex position and color data
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, VertexSize, vertices[0]);
	offset += VertexSize;
	//send index in the same buffer
	indexBufferOffset = offset;
	glBufferSubData(GL_ARRAY_BUFFER, offset, IndexSize, indices[0]);
	offset += IndexSize;

	//enable vertex attrib pointer and information about data
	glEnableVertexAttribArray(0);		//position


	//assign attribute pointer
	GLuint currBufferOffset = 0;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(currBufferOffset));
	currBufferOffset += VertexSize;


	//unbind VAO, VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);


	//create shader do after 
	objectShader = new Shader(SHADER_PATH"vsTestPlyModel.txt", SHADER_PATH"fsTestPlyModel.txt");
}

void TestPlyModel::render()
{
	//bind the shader program
	objectShader->Bind();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, BUFFER_OFFSET(indexBufferOffset));
	glBindVertexArray(0);

	//unbind the shader
	objectShader->Unbind();
}

void TestPlyModel::initData()
{
	//store the vertices in local variable
	vertices = plyreader->getVertices();

	//store the indices in local variable
	indices = plyreader->getIndices();
}
