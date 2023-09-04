#pragma once
#include<map>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

class ResourceManager
{
	//sound, font, texture
public:
	// load함수랑(이름-key와 경로 받은 함수)
	void LoadSoundBuf(std::string key, std::string path);
	void LoadTexture(std::string key, std::string path);
	void LoadFont(std::string key, std::string path);
	// get함수(이름-key 넣어서 가져올 수 있게
	const sf::SoundBuffer& GetSoundBuf(std::string key) const { return m_soundbufs.at(key); }
	const sf::Texture& GetTexture(std::string key) const { return m_textures.at(key); }
	const sf::Font& GetFont(std::string key) const { return m_fonts.at(key); }
private:
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, sf::Font> m_fonts;
	std::map<std::string, sf::SoundBuffer> m_soundbufs;
};

