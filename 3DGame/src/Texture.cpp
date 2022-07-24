#include "Texture.h"
#include <GL/glew.h>
#include <SDL/SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture() : mTextureID(0), mWidth(0), mHeight(0) {}

Texture::~Texture() {}

bool Texture::Load(const std::string& fileName) {
	mFileName = fileName;
	int channels = 0;
	unsigned char* image = stbi_load(fileName.c_str(), &mWidth, &mHeight, &channels, 0);

	if (image == nullptr) {
		SDL_Log("Failed to load image %s: %s", fileName.c_str());
		return false;
	}
	SDL_Log("Texture Name: %s, Size: %d x %d, Channels: %d", fileName.c_str(), mHeight, mWidth, channels);

	int format = GL_RGB;
	if (channels == 4) {
		format = GL_RGBA;
	}
	// Search unused texture ID.
	glGenTextures(1, &mTextureID);
	// Upload texture to VRAM, make OpenGL texture object.
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	// copy raw image data.
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format,
		GL_UNSIGNED_BYTE, image);
	// Free SOIL image data from memory.
	stbi_image_free(image);

	// Generate mipmaps for texture
	glGenerateMipmap(GL_TEXTURE_2D);
	// Enable linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Enable aniostropic filtering, if supported
	if (GLEW_EXT_texture_filter_anisotropic) {
		// Get the maximum anisotropy value
		GLfloat largest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
		// Enable it
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
	}

	return true;
}

void Texture::Unload() { glDeleteTextures(1, &mTextureID); }

void Texture::CreateFromSurface(SDL_Surface* surface) {
	mWidth = surface->w;
	mHeight = surface->h;

	// Generate a GL texture
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, surface->pixels);

	// Use linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::CreateForRendering(int width, int height, unsigned int format) {
	mWidth = width;
	mHeight = height;
	// Create the texture id
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// Set the image width/height with null initial data
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, GL_RGB, GL_FLOAT,
		nullptr);

	// For a texture we'll render to, just use nearest neighbor
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::SetActive(int index) {
	// ここをGL_TEXTUREに設定してたせいでテクスチャが１種類しか読めない状態になってた
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}
