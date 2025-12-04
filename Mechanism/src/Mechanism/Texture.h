#pragma once

#include "Core.h"
#include <string>


namespace Mechanism 
{

	class MECHANISM_API Texture
	{

	public:
		Texture(void* renderer ,const std::string& filepath);
		~Texture();
		
		
	private:
		
		void LoadTexture(void* renderer, const std::string& filepath);

		void* m_Texture = nullptr;
		std::string m_Filepath;

	};

}