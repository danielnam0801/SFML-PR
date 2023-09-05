#pragma once
#include<stack>
#include<memory>
#include "Scene.h"
class Scene;
class SceneManager
{
public:
	// Scene 추가(등록)
	void AddScene(std::unique_ptr<Scene> _newScene, bool _isChanging = true);
	void SetRemoveScene() { m_isRemoving = true; }
	// Scene 변경.
	void ChangeScene();

	//현재 씬
	const std::unique_ptr<Scene>& GetCurScene() const {
		return m_Scenes.top();
	}
private:
	std::stack<std::unique_ptr<Scene>> m_Scenes;
	std::unique_ptr<Scene> m_newScene;
	bool m_isRemoving;
	bool m_isAdding;
	bool m_isChanging;
};

