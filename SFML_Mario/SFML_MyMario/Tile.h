#pragma once
#include "Object.h"
class Tile :
    public Object
{
public:
    Tile(Vector2f _pos, Vector2f _scale);
    void Update(float _dt) override;
    void Render() override;
};

