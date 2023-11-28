#pragma once
class Object;
class Rigidbody
{
private:
	Object* m_pOwner;
	friend class Object;
};

