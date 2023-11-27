#pragma once
#include "Object.h"
class Player :
    public Object
{
public:
    virtual void Update(float _dt) override;
    virtual void Render() override;
public:
    const Sprite& GetSprite() const
    {
        return m_sprite;
    }
private:
    Sprite m_sprite;
};

