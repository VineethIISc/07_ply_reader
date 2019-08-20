/*
Currently support:
1) binary format->little_endian format 
2) vertices in the model

Greg Turk
reference: http://gamma.cs.unc.edu/POWERPLANT/papers/ply.pdf
for reading the binary format
reference; https://medium.com/@elope139/reading-ply-files-that-are-in-binary-format-cab3a37276a2

*/

#ifndef PLY_READER_H
#define PLY_READER_H

#include "CommonHeader.h"

#define PLY_MAGIC_NUMBER "ply"

#define PLY_ASCII 1
#define PLY_BINARY 2

#define PLY_FORMAT "format"
#define PLY_ASCII_FORMAT "ascii"
#define PLY_END_HEADER "end_header"

#define PLY_PROPERTY "property"
#define PLY_FLOAT "float"

#define PLY_ELEMENT "element"
#define PLY_VERTEX "vertex"
#define PLY_FACE "face"
#define PLY_NORMAL "normal"

#define NUM_INDICES_TRI 3

//in bytes
#define PLY_VERTEX_SIZE_TRI 12
#define PLY_FACE_START_NUM_SIZE 1  
#define PLY_INDICES_SIZE_TRI 12

class PLYreader
{
public:
	PLYreader(const std::string& filename);
	

	//getters 
	int getNumberOfFaces();	//get number of faces
	void printNumberOfFaces();	//print number of faces

	int getNumberOfVertices();	//get number of vertices
	void printNumberOfVertices();	//print number of vertices

	int	getNumberOfIndices();//get number of indices

	std::vector<Vector3f>& getVertices();	//return the address of the vertices
	std::vector<Vector3ui>& getIndices();	//return the address of the indices

private:
	//check whether the given file is ascii or binary
	void readHeader(std::ifstream& input);

	//read ascii ply file
	void readASCIIply(std::ifstream& input);

	//read binary ply file
	void readBINARYply(std::ifstream& input);

private:
	//format
	int fileFormat;
	int plyNumVertCoord;

	//number of facet
	unsigned int numberOfTriangles;
	unsigned int numberOfvertices;

	//storage
	std::vector<Vector3f> vertices;
	std::vector<Vector3f> normals;
	std::vector<Vector3ui> indices;

};
#endif // !PLY_READER_H



