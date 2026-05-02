#pragma once

#include <filesystem>
#include <iostream>

#include "stb_image.h"
#include "glad/gl.h"

class Texture
{
public:
	unsigned int ID;

	explicit Texture(const std::filesystem::path& path)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);

		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD" << std::endl;
		}

		stbi_image_free(data);
	}

	~Texture()
	{
		glDeleteTextures(1, &ID);
	}
	
	void bind()
	{
		if (ID)
			glBindTexture(GL_TEXTURE_2D, ID);
	}
};