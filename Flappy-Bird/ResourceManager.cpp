#include "ResourceManager.h"
#include <iostream>

void ResourceManager::LoadSoundBuf(std::string key, std::string path)
{
	sf::SoundBuffer  soundBuf;
	if (soundBuf.loadFromFile(path))
	{
		m_soundbufs[key] = soundBuf;
	}
	else {
		std::cout << "soundbuf load error" << std::endl;
	}
}

void ResourceManager::LoadTexture(std::string key, std::string path)
{
	sf::Texture  tex;
	if (tex.loadFromFile(path))
	{
		m_textures[key] = tex;
	}
	else {
		std::cout << "texture load error" << std::endl;
	}

}

void ResourceManager::LoadFont(std::string key, std::string path)
{
	sf::Font  font;
	if (font.loadFromFile(path))
	{
		m_fonts[key] = font;
	}
	else {
		std::cout << "font load error" << std::endl;
	}
}
