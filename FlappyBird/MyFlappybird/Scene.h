#pragma once
class Scene
{
public:
	virtual void Init() abstract;
	virtual void Update(float _dt) abstract;
	virtual void Render() abstract;
};

