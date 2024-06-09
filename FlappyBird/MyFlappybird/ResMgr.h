#pragma once
#include<map>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
class ResMgr
{
	// sound, font, texture
public:
	// load�Լ���(�̸�-key�� ��� ���� �Լ�)
	void LoadTexture(std::string _name, std::string _filepath);
	void LoadFont(std::string _name, std::string _filepath);
	void LoadSoundbuf(std::string _name, std::string _filepath);
	// get�Լ�(�̸�-key �־ �����ü��ְ�)
	const sf::Texture& GetTexture(std::string _name) const { return m_textures.at(_name); }
	const sf::Font& GetFont(std::string _name) const { return m_fonts.at(_name); }
	const sf::SoundBuffer& GetSoundbuf(std::string _name) const { return m_soundbufs.at(_name); }

private:
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, sf::Font> m_fonts;
	std::map<std::string, sf::SoundBuffer> m_soundbufs;
};

