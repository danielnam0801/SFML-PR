#pragma once
class ResMgr
{
private:
    ResMgr() {}
    ~ResMgr() {}
public:
    static ResMgr* GetInst()
    {
        static ResMgr Inst;
        return &Inst;
    }
public:
    void LoadTexture(std::string _name, std::string _filename);
    const sf::Texture& GetTexture(std::string _name) const { return m_textures.at(_name); }

    void LoadFont(std::string _name, std::string _filename);
    const sf::Font& GetFont(std::string _name) const { return m_fonts.at(_name); }

    void LoadSoundbuf(std::string _name, std::string _filename);
    const sf::SoundBuffer& GetSound(std::string _name) const { return m_Soundbufs.at(_name); }

private:
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, sf::Font> m_fonts;
    std::map<std::string, sf::SoundBuffer> m_Soundbufs;
};
