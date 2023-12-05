#include "pch.h"
#include "Scene.h"
#include "Object.h"
Scene::Scene()
{
}
Scene::~Scene()
{
	Release();
}
void Scene::Init()
{
}
void Scene::Update(float _dt)
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			if (!m_vecObj[i][j]->GetIsDead())
				m_vecObj[i][j]->Update(_dt);
		}
	}
}

void Scene::FinalUpdate(float _dt)
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			m_vecObj[i][j]->FinalUpdate(_dt);
		}
	}
}

void Scene::Render()
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size();)
		{
			if (!m_vecObj[i][j]->GetIsDead())
			{
				m_vecObj[i][j]->Render();
				++j;
			}
			else
				m_vecObj[i].erase(m_vecObj[i].begin() + j);
		}
	}
}

void Scene::Release()
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			if (nullptr != m_vecObj[i][j])
				delete m_vecObj[i][j];
		}
		m_vecObj[i].clear();
	}
}