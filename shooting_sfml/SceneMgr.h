#pragma once
class Scene;
class SceneMgr
{
    SINGLE(SceneMgr);
public:
    void RegisterScene(const string& _sceneName, std::shared_ptr<Scene> _scene);
    void LoadScene(const string& _sceneName);
public:
    void    Init();
    void    Update(const float& _dt);
    void    Render();
private:
    std::shared_ptr<Scene>                m_pCurScene; // ���� ��
    map<string, std::shared_ptr<Scene>> m_mapScenes; // ��� �� ��� map���� ����
};