#pragma once
class Object;
class Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void Init() abstract;
	virtual void Update(float _dt);
	virtual void FinalUpdate(float _dt);
	virtual void Render();
	virtual void Release();
public:
	const vector<Object*>& GetGroupObject(OBJECT_GROUP _etype) const
	{
		return m_vecObj[(int)_etype];
	}
public:
	void AddObject(Object* _pObj, OBJECT_GROUP _eType)
	{
		m_vecObj[(int)_eType].push_back(_pObj);
	}
private:
	vector<Object*> m_vecObj[(int)OBJECT_GROUP::END];
};

