#ifndef STL_READER_H
#define STL_READER_H

#include "CommonHeader.h"

#define STL_ASCII 1
#define STL_BINARY 2

//memory in bytes 
#define STL_BINARY_HEADER_SIZE 80
#define STL_BINARY_TRIANGLE_SIZE 50
#define STL_BINARY_TRIANGLE_NORMAL_SIZE 12
#define STL_BINARY_TRIANGLE_VERTEX_SIZE 12
#define STL_BINARY_TRIANGLE_ATTRIBUTE_SIZE 2
#define STL_NUM_VERTEX_PER_FACE 3

//definition
#define STL_SOLID_START "solid"
#define STL_SOLID_SIZE 5
#define STL_CHECK_LINE 3

#define STL_FACE "facet"
#define STL_END_FACE "endfacet"

#define STL_VERTEX "vertex"
#define STL_NORMAL "normal"


class STLreader
{
public:
	//construct take the file name as argument
	STLreader(const std::string& filename);

	//getters 
	int getNumberOfFaces();	//get number of faces
	void printNumberOfFaces();	//print number of faces

	int getNumberOfVertices();	//get number of vertices
	void printNumberOfVertices();	//print number of vertices

	std::vector<Vector3f>& getVertices();	//return the address of the vertices

private:
	//check whether the given file is ascii or binary
	int checkFormat(std::ifstream& input);
	
	//check end of file to confirm ascii
	bool checkForFacet(std::ifstream& input);

	//read ascii stl file
	void readASCIIstl(std::ifstream& input);

	//read binary stl file
	void readBINARYstl(std::ifstream& input);

private:
	//format
	int fileFormat;

	//number of facet
	uint32_t numberOfTriangles;
	int numberOfvertices;

	//storage
	std::vector<Vector3f> vertices;
	std::vector<Vector3f> normals;
};



#endif // ! STL_READER_H

