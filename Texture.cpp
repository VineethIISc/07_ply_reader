#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& name): textureObject(0)
{
	//read the texture data from file
	stbi_set_flip_vertically_on_load(true);	//flip the y-axis

	//add the complete file path
	std::string fileName = IMAGE_PATH + name;

	//load data from file to CPU
	textureData = stbi_load(fileName.c_str(), &textureWidth, &textureHeight, &colorChannels, 0);
}


Texture::~Texture()
{
}

void Texture::UseTexture(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureObject);
}

void Texture::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::loadTexture()
{
	//generate a texture object
	glGenTextures(1, &textureObject);

	//bind the texture object to target : 2D texture
	glBindTexture(GL_TEXTURE_2D, textureObject);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);		//wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	//mip map filtering 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//careful to not assign mip map option

	//pass data from CPU to GPU (only if some data is there)
	if (textureData)
	{
		if(colorChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		else if(colorChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

		glGenerateMipmap(GL_TEXTURE_2D);	//opengl generate different level of mipmap
	}
	else
		std::cout << "Failed to load texture to GPU" << std::endl;

	stbi_image_free(textureData);		//delete the data from CPU

	//unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}