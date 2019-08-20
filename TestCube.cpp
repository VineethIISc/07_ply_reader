#include "Shader.h"
#include "STLreader.h"
#include "TestCube.h"


TestCube::TestCube() :VBO(0), VAO(0), objectShader(NULL)
{
	stlFileReader = new STLreader(MODEL_PATH"chair.stl");
	
	//draw all vertices
	numVertices = stlFileReader->getNumberOfVertices();

	//create vertices and color
	initVertexData();	
}


TestCube::~TestCube()
{
	if (VAO)
		glDeleteVertexArrays(1, &VAO);

	if (VBO)
		glDeleteBuffers(1, &VBO);

	if (stlFileReader)
		delete stlFileReader;
	
	if (objectShader)
		delete objectShader;
}

GLuint TestCube::getVBO()
{
	return VBO;
}

GLuint TestCube::getVAO()
{
	return VAO;
}

void TestCube::initVertexData()
{
	//store the reference in local variable
	vertices = stlFileReader->getVertices();	
}

void TestCube::loadData()
{
	//create vertex array objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind VAO, VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//allocate memory in GPU
	GLsizeiptr VertexSize = sizeof(Vector3f) * numVertices;
	GLsizeiptr TotalSize = VertexSize;
	glBufferData(GL_ARRAY_BUFFER, TotalSize, NULL, GL_STATIC_DRAW);

	//pass vertex position and color data
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, VertexSize, vertices[0]);
	offset += VertexSize;
	
	//enable vertex attrib pointer and information about data
	glEnableVertexAttribArray(0);		//position
	

	//assign attribute pointer
	GLuint currBufferOffset = 0;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(currBufferOffset));
	currBufferOffset += VertexSize;
	

	//unbind VAO, VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	

	//create shader do after 
	objectShader = new Shader(SHADER_PATH"vsTestCube.txt", SHADER_PATH"fsTestCube.txt");

}

void TestCube::render()
{
	//bind the shader program
	objectShader->Bind();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);		//full cube
	glBindVertexArray(0);
	
	//unbind the shader
	objectShader->Unbind();
}