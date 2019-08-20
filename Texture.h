#ifndef TEXTURE_H
#define TEXTURE_H

#include "CommonHeader.h"

class Texture
{
public:
	Texture(const std::string& name);
	~Texture();

	//methods for bind, unbind and load the texture
	void UseTexture(GLenum textureUnit);
	void unbindTexture();
	void loadTexture();

private:
	//textureObject
	GLuint textureObject;

	//store the texture values
	unsigned char* textureData;	

	//texture details
	int textureWidth;	//width of texture
	int textureHeight;  //height of texture
	int colorChannels; //number of colorchannels in texture RGB/ RGBA

};
#endif // !TEXTURE_H



