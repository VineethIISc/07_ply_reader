#include "PLYreader.h"



PLYreader::PLYreader(const std::string& filename): plyNumVertCoord(0), fileFormat(0), numberOfTriangles(0), numberOfvertices(0)
{
	//read the file as stream
	std::ifstream inputFile(filename, std::ios::binary);
	if (!inputFile)
	{
		std::cout << "Failed to load the file: " << filename << std::endl;
		return;
	}

	std::string data;
	inputFile >> data;

	//check whether the input file is ply or not
	if (data == PLY_MAGIC_NUMBER)
	{
		//check for the format of input file 
		readHeader(inputFile);

		//read the file using respective methods
		if (fileFormat == PLY_ASCII)
			readASCIIply(inputFile);
		else
			readBINARYply(inputFile);
	}
	else
		std::cout << "File is not ply: " << filename << std::endl;
	

	//close the file
	inputFile.close();
}


int PLYreader::getNumberOfFaces()
{
	return numberOfTriangles;
}

void PLYreader::printNumberOfFaces()
{
	std::cout << "number of Faces: " << numberOfTriangles << std::endl;
}

int PLYreader::getNumberOfVertices()
{
	return numberOfvertices;
}

void PLYreader::printNumberOfVertices()
{
	std::cout << "number of Vertices: " << numberOfvertices << std::endl;
}

int PLYreader::getNumberOfIndices()
{
	return NUM_INDICES_TRI * getNumberOfFaces();
}

std::vector<Vector3f>& PLYreader::getVertices()
{
	return vertices;
}

std::vector<Vector3ui>& PLYreader::getIndices()
{
	return indices;
}

void PLYreader::readHeader(std::ifstream& input)
{
	std::string data;
	
	//read till end of header
	do
	{
		input >> data;
		if (data == PLY_FORMAT)
		{
			input >> data;
			if (data == PLY_ASCII_FORMAT)
			{
				fileFormat = PLY_ASCII;
				continue;
			}
			else
			{
				fileFormat = PLY_BINARY;
				continue;
			}
		}
		if (data == PLY_VERTEX)
		{
			input >> numberOfvertices;
			input >> data;

			//next string "property"
			while (data == PLY_PROPERTY)
			{
				input >> data;
				if (data == PLY_FLOAT)
				{
					plyNumVertCoord++;
					std::string x;
					input >> x;
					input >> data;
				}
			}

		}
		else if (data == PLY_FACE)
		{
			input >> numberOfTriangles;
		}
	} while (data != PLY_END_HEADER);

}

void PLYreader::readASCIIply(std::ifstream& input)
{
	//read all vertices
	for (unsigned int i = 0; i < numberOfvertices; i++)
	{
		Vector3f v;
		input >> v.x >> v.y >> v.z;

		vertices.push_back(v);
	}

	//read all faces
	for (unsigned int i = 0; i < numberOfTriangles; i++)
	{
		//read the first number in each face
		unsigned char start;
		input >> start;

		//check if it is 3 for triangle
		Vector3ui ind;
		if (start == NUM_INDICES_TRI)
			input >> ind.a >> ind.b >> ind.c;
		else
			std::cout << "Face is not triangle" << std::endl;

		indices.push_back(ind);
	}

	std::cout << "Done reading the PLY" << std::endl;
	
}

void PLYreader::readBINARYply(std::ifstream& input)
{
	
	//set the file get pointer to beginning
	input.seekg(0, std::ios::beg);

	//skip the header
	std::string line;
	do 
	{
		std::getline(input, line);
	}while (line != PLY_END_HEADER);


	//read all vertices
	for (unsigned int i = 0; i < numberOfvertices; i++)
	{
		//read a vertex: contain 3 coordinates
		Vector3f v;
		input.read((char*)& v, PLY_VERTEX_SIZE_TRI);
		vertices.push_back(v);
	}

	//read all indices
	for (unsigned int i = 0; i < numberOfTriangles; i++)
	{
		//read the start value
		unsigned int start;
		input.read((char*)&start, PLY_FACE_START_NUM_SIZE);

		//read the faces: in term of indices
		if (start == NUM_INDICES_TRI)
		{
			Vector3ui ind;
			input.read((char*)& ind, PLY_INDICES_SIZE_TRI);
			indices.push_back(ind);
		}
		else
			std::cout << "Face is not triangle" << std::endl;
		
	}

	std::cout << "Done reading the PLY" << std::endl;
}
