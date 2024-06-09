#pragma once
#include "Object.h"
class DefTile :
    public Object
{
public:
    DefTile(Sprite& _sprite);
public:
    virtual void Update(float _dt) override;
    virtual void Render() override;
};

