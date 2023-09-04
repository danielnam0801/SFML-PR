#pragma once
#include<map>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

class ResourceManager
{
	//sound, font, texture
public:
	// load�Լ���(�̸�-key�� ��� ���� �Լ�)
	void LoadSoundBuf(std::string key, std::string path);
	void LoadTexture(std::string key, std::string path);
	void LoadFont(std::string key, std::string path);
	// get�Լ�(�̸�-key �־ ������ �� �ְ�
	const sf::SoundBuffer& GetSoundBuf(std::string key) const { return m_soundbufs.at(key); }
	const sf::Texture& GetTexture(std::string key) const { return m_textures.at(key); }
	const sf::Font& GetFont(std::string key) const { return m_fonts.at(key); }
private:
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, sf::Font> m_fonts;
	std::map<std::string, sf::SoundBuffer> m_soundbufs;
};

