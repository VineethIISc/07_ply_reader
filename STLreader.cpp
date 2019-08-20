#include "STLreader.h"



STLreader::STLreader(const std::string& filename): fileFormat(0), numberOfTriangles(0), numberOfvertices(0)
{
	//read the file as stream
	std::ifstream inputFile(filename, std::ios::binary);
	if (!inputFile)
	{
		std::cout << "Failed to load the file: " << filename << std::endl;
		return;
	}

	//check for the format of input file 
	fileFormat = checkFormat(inputFile);
	
	//read the file using respective methods
	if (fileFormat == STL_ASCII)
		readASCIIstl(inputFile);
	else 
		readBINARYstl(inputFile);

	//close the file
	inputFile.close();

}


int STLreader::checkFormat(std::ifstream& input)
{
	//read first 5 bytes
	char format[STL_SOLID_SIZE + 1];
	input.read(format, STL_SOLID_SIZE);
	format[STL_SOLID_SIZE] = '\0';	//write the end character 

	//compare the array of character if it is solid then file format is ascii
	//otherwise it is binary
	if (strcmp(format, STL_SOLID_START) == 0)
	{
		//search for facet word
		if(checkForFacet(input))
			return STL_ASCII;
	}

	return STL_BINARY;
}

bool STLreader::checkForFacet(std::ifstream& input)
{
	std::string line;
	for (int i = 0; i < STL_CHECK_LINE; i++)
	{
		//check for eof
		if (std::getline(input, line))
		{
			std::string search = STL_FACE;
			size_t found = line.find(search);
			//if found facet in line: "ASCII file format cofirmed"
			if (found != std::string::npos)
				return true;
		}	
	}
	
	return false;
}

void STLreader::readASCIIstl(std::ifstream& input)
{
	//set the file get pointer to beginning
	input.seekg(0, std::ios::beg);

	//read till end of file
	while (input)
	{
		std::string data;
		input >> data;

		if (data == STL_FACE)
		{
			do
			{
				input >> data;
				if (data == STL_VERTEX)
				{
					Vector3f v;
					input >> v.x >> v.y >> v.z;
					vertices.push_back(v);
				}
				else if (data == STL_NORMAL)
				{
					Vector3f n;
					input >> n.x >> n.y >> n.z;
					normals.push_back(n);
				}

			} while (data != STL_END_FACE);
			
			//one face is read
			numberOfTriangles++;
		}
	}
	printNumberOfFaces();
}

void STLreader::readBINARYstl(std::ifstream& input)
{
	//set the file get pointer to beginning
	input.seekg(0, std::ios::beg);
	
	//read the header whose size is 80 bytes
	char header[STL_BINARY_HEADER_SIZE + 1];
	input.read(header, STL_BINARY_HEADER_SIZE);
	header[STL_BINARY_HEADER_SIZE] = '\0';

	//read 4bytes or 32bit unsinged int for number of triangles
	input.read((char*)&numberOfTriangles, sizeof(uint32_t));

	//read the triangles and data of each faces
	for (uint32_t i = 0; i < numberOfTriangles; i++)
	{
		//read normals which are 3 floats or 12 bytes or 48bit
		Vector3f n;
		input.read((char*)& n, STL_BINARY_TRIANGLE_NORMAL_SIZE);
		normals.push_back(n);

		//for each face there will be three vertices
		for (int j = 0; j < STL_NUM_VERTEX_PER_FACE; j++)
		{
			//read vertex which are 3 floats or 12 bytes or 48 bit
			Vector3f v;
			input.read((char*)& v, STL_BINARY_TRIANGLE_NORMAL_SIZE);
			vertices.push_back(v);
		}

		//read 2bytes or 16bit attribute count
		uint16_t attributeCount;
		input.read((char*)& attributeCount, STL_BINARY_TRIANGLE_ATTRIBUTE_SIZE);
		if (attributeCount)
			std::cout << "Alert!!!!!!!!!!! Attribute Count: " << attributeCount << std::endl;
		
	}
	printNumberOfFaces();
}

int STLreader::getNumberOfFaces()
{ 
	return numberOfTriangles;
}

void STLreader::printNumberOfFaces() 
{
	std::cout << "number of Faces: " << numberOfTriangles << std::endl;
}

int STLreader::getNumberOfVertices()
{
	return (numberOfvertices = STL_NUM_VERTEX_PER_FACE * getNumberOfFaces());
}

void STLreader::printNumberOfVertices()
{
	std::cout << getNumberOfVertices() << std::endl;
}

std::vector<Vector3f>& STLreader::getVertices()
{
	return vertices;
}
