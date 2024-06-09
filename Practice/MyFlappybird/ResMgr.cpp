#include "ResMgr.h"
#include<iostream>
void ResMgr::LoadTexture(std::string _name, std::string _filepath)
{
	sf::Texture tex;
	if (tex.loadFromFile(_filepath))
		m_textures[_name] = tex;
	else
		std::cout << "texture load error" << std::endl;
}

void ResMgr::LoadFont(std::string _name, std::string _filepath)
{
	sf::Font font;
	if (font.loadFromFile(_filepath))
		m_fonts[_name] = font;
	else
		std::cout << "font load error" << std::endl;
}

void ResMgr::LoadSoundbuf(std::string _name, std::string _filepath)
{
	sf::SoundBuffer soundbuf;
	if (soundbuf.loadFromFile(_filepath))
		m_soundbufs[_name] = soundbuf;
	else
		std::cout << "soundbuf load error" << std::endl;
}
