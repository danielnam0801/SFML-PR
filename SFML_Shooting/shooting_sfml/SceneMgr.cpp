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
    // ���� ������..
    if (m_pCurScene != nullptr)
    {
        m_pCurScene->Release();
        m_pCurScene = nullptr;
    }

    // �ε��� ���� ã�Ƽ�..
    auto iter = m_mapScenes.find(_sceneName);
    // �װ� ���� �ƴϸ�
    if (iter != m_mapScenes.end())
    {
        m_pCurScene = iter->second;
        m_pCurScene->Init();
    }
}

void SceneMgr::Init()
{
    // ����� nullptr �ʱ�ȭ
    m_pCurScene = nullptr;
    // �� ���
    RegisterScene("Menu_Scene", std::make_shared<MenuScene>());
    RegisterScene("Game_Scene", std::make_shared<GameScene>());
//    // ù �� ����
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