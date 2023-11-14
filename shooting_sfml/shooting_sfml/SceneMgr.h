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
    const std::shared_ptr<Scene>& GetCurScene() const { return m_pCurScene; }
private:
    std::shared_ptr<Scene>                m_pCurScene; // 현재 씬
    map<string, std::shared_ptr<Scene>> m_mapScenes; // 모든 씬 목록 map으로 관리
};