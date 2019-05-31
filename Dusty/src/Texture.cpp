#include "Texture.h"

#include <SDL/SDL_image.h>

namespace dusty
{
	Texture::Texture(const std::string& path)
		: m_Path(path)
		, m_Source(nullptr)
	{}

	Texture::~Texture()
	{
		if (m_Source)
		{
			SDL_FreeSurface(m_Source);
			m_Source = nullptr;
		}
	}

	bool Texture::Load() 
	{
		const char* path = m_Path.c_str();
		m_Source = IMG_Load(path);
		
		if (m_Source == nullptr)
		{
			SDL_Log("Unable To Load Texture : %s\n", path);
			return false;
		}

		SDL_Log("Texture : %s Loaded Successfully\n", path);

		return true;
	}
}