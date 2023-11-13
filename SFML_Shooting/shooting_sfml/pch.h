#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include<string>
#include<algorithm>
#define _USE_MATH_DEFINES
#include<math.h>
#include"define.h"
using std::vector;
using std::map;
using std::string;
using namespace sf;
#define SINGLE(type)        \
private:                    \
    type() {}                \
    ~type() {}                \
public:                        \
    static type* GetInst()    \
    {                        \
        static type mgr;    \
        return &mgr;        \
    }
#include "ResMgr.h"
#include "SceneMgr.h"
#include "WindowMgr.h"
#include "InputMgr.h"
enum class ENEMY
{
    MOVEDOWN, FOLLOW, FOLLOWSHOOT,
    FOLLOWFAST, FOLLOWFASTSHOOT,
    ELITE, BOSS1,
};
enum class WEAPON
{
    LASER_R, MISSILE01, MISSILE02, ENEMYBULLET, SPLIT, ROTATE, DOUBLE, TRIPLE, BOMB
};

enum class ITEM_TYPE
{
    HP_KIT, STAT_POINT,
    HPMAXUP, DOUBLE, TRIPLE,
    PIERCING, SHILED
};

enum class GAME_STAGE
{
    NONE, STAGE01, STAGE02, STAGE03,
    ELITE, BOSS, END
};

enum class ELITE_STAGE
{
    IDLE, ATTACTK_DEFAULT,
    ATTACTK_CIRCLE, ATTACK_AROUND
};