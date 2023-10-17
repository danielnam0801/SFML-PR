#pragma once
class Core
{
public:
    Core(int _width, int _height, std::string _title);
    void Run();
    void Update(const float& _dt);
    void Render();
private:
    const float m_dt = 1.0f / 60.0f; // 60 fps으로 고정
    sf::Clock m_clock;
    void PollEvent();
    void Init();
};