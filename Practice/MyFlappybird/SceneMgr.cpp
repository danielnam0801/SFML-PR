#include "SceneMgr.h"
#include "Scene.h"
void SceneMgr::AddScene(std::unique_ptr<Scene> _newScene, bool _isChanging)
{
	m_newScene = std::move(_newScene);
	m_isAdding = true;
	m_isChanging = _isChanging;
}

void SceneMgr::ChangeScene()
{
	// ¾À Á¦°ÅÇØ¾ßÇÏ´Â »óÅÂ°í, ¾ÀÀÌ ÀÖÀ¸¸é ¾ÀÀ» »©¶ó.
	if (m_isRemoving && !m_Scenes.empty())
	{
		m_Scenes.pop();
		m_isRemoving = false;
	}
	// ¾À Ãß°¡µÇ¾î¾ßÇÏ´Â »óÅÂ°í, ¾ÀÀÌ ÀÖÀ¸¸é, ¾ÀÀ» »©°í, »õ·Î¿î ¾ÀÀ» ³Ö¾î¶ó.
	if (m_isAdding)
	{
		if (m_isChanging && !m_Scenes.empty())
			m_Scenes.pop();
		m_Scenes.push(std::move(m_newScene));
		m_Scenes.top()->Init();
		m_isAdding = false;
	}
}
