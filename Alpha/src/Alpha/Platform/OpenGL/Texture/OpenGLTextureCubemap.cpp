#include "appch.h"

#include "OpenGLTextureCubemap.h"
#include "glad/glad.h"

#include "stb_image.h"

namespace Alpha
{
	OpenGLTextureCubemap::OpenGLTextureCubemap(const std::array<std::string, 6>& filepaths)
		: m_FilePaths(filepaths), m_Height(0), m_Width(0)
	{
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < 6; i++)
		{

			stbi_set_flip_vertically_on_load(1);
			unsigned char* data = stbi_load(filepaths[i].c_str(), &width, &height, &nrChannels, 0);
			if(!data)
			{
				AP_CORE_ERROR(filepaths[i])
				AP_ASSERT(false, "Image couldnt be loaded!")
			}

				GLenum internalFormat = 0, dataFormat = 0;
			if (nrChannels == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (nrChannels == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, dataFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	OpenGLTextureCubemap::OpenGLTextureCubemap(const std::string& filepath)
		: m_FilePaths({ filepath, filepath, filepath, filepath, filepath, filepath }), m_Height(0), m_Width(0)
	{
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

		int width, height, nrChannels;

		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

		AP_ASSERT(data, "Image couldnt be loaded!")

			GLenum internalFormat = 0, dataFormat = 0;
		if (nrChannels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (nrChannels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		for (unsigned int i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, dataFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		}

		stbi_image_free(data);


		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	OpenGLTextureCubemap::~OpenGLTextureCubemap()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTextureCubemap::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
	}
}
