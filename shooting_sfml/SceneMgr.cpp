#include "pch.h"
#include "SceneMgr.h"
#include "MenuScene.h"
#include "GameScene.h"
void SceneMgr::RegisterScene(const string& _sceneName, std::shared_ptr<Scene> _scene)
{
    m_mapScenes.insert(m_mapScenes.end(), { _sceneName, _scene });
}

void SceneMgr::LoadScene(const string& _sceneName)
{
    // 씬이 있으면..
    if (m_pCurScene != nullptr)
    {
        m_pCurScene->Release();
        m_pCurScene = nullptr;
    }

    // 로드할 씬을 찾아서..
    auto iter = m_mapScenes.find(_sceneName);
    // 그게 끝이 아니면
    if (iter != m_mapScenes.end())
    {
        m_pCurScene = iter->second;
        m_pCurScene->Init();
    }
}

void SceneMgr::Init()
{
    // 현재씬 nullptr 초기화
    m_pCurScene = nullptr;
    // 씬 등록
    RegisterScene("Menu_Scene", std::make_shared<MenuScene>());
    RegisterScene("Game_Scene", std::make_shared<GameScene>());
//    // 첫 씬 지정
////    LoadScene("Game_Scene");
    LoadScene("Menu_Scene");
}

void SceneMgr::Update(const float& _dt)
{
    m_pCurScene->Update(_dt);
}

void SceneMgr::Render()
{
    m_pCurScene->Render();
}