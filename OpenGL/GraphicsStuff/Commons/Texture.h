#pragma once
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <glad/glad.h>
#include <cstdint>
#include "stb_image.h"

class Texture
{
private:
	uint32_t id;
	int32_t mode;
	int32_t width, height, numChannels;
	
public:

	Texture(const char* path, int32_t mode, bool alpha = true, int32_t wrapS = GL_REPEAT,
		int32_t wrapT = GL_REPEAT, int32_t magFilter = GL_LINEAR, int32_t minFilter = GL_LINEAR) : mode{ mode }
	{	
		int32_t loadMode = alpha ? GL_RGBA : GL_RGB;
		glGenTextures(1, &id);
		glBindTexture(mode, id);
		glTexParameteri(mode, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(mode, GL_TEXTURE_WRAP_T, wrapT);
		glTexParameteri(mode, GL_TEXTURE_MAG_FILTER, magFilter);
		glTexParameteri(mode, GL_TEXTURE_MIN_FILTER, minFilter);

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path, &width, &height, &numChannels, 0);
		if (data) {
			glTexImage2D(mode, 0, GL_RGB, width, height, 0, loadMode, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(mode);
			stbi_image_free(data);
		}
		glBindTexture(mode, 0);
	}

	void Bind()
	{
		glBindTexture(mode, id);
	}
};