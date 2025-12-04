#include "Texture.h"
#include "SDL3/SDL.h"
#include "glad/glad.h"
#include <iostream>

namespace Mechanism
{

	Texture::Texture(void* renderer , const std::string& filepath) : m_Filepath(filepath)
	{
		LoadTexture(renderer, filepath);
	}

	Texture::~Texture()
	{
		if(m_Texture)
		{
			SDL_DestroyTexture(static_cast<SDL_Texture*>(m_Texture));
		}
	}

	void Texture::LoadTexture(void* renderer ,const std::string& filepath)
	{
		SDL_Renderer* sdlRenderer = static_cast<SDL_Renderer*>(renderer);
		SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);

		if(!surface)
		{
			std::cerr << "Failed to load the .bmp texture: " << filepath << std::endl;
			std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
			return;
		}

		if(!texture)
		{
			std::cerr << "Failed to create texture from surface: " << filepath << std::endl;
			std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
			return;
		}

		SDL_DestroySurface(surface);
		m_Texture = texture;
		std::cout << "BMP Texture loaded: " << filepath << std::endl;
	}

}