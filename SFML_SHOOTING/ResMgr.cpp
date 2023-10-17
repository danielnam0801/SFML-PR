#include "pch.h"
#include "ResMgr.h"

void ResMgr::LoadTexture(std::string _name, std::string _filename)
{
    sf::Texture tex;
    if (tex.loadFromFile(_filename))
        m_textures[_name] = tex;
    else
        std::cout << "texture load error" << std::endl;
}

void ResMgr::LoadFont(std::string _name, std::string _filename)
{
    sf::Font font;
    if (font.loadFromFile(_filename))
        m_fonts[_name] = font;
    else
        std::cout << "font load error" << std::endl;
}

void ResMgr::LoadSoundbuf(std::string _name, std::string _filename)
{
    sf::SoundBuffer soundbuf;
    if (soundbuf.loadFromFile(_filename))
        m_Soundbufs[_name] = soundbuf;
    else
        std::cout << "sound load error" << std::endl;
}