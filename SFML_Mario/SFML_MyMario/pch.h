#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include<string>
#include<algorithm>
#include <Windows.h>
#include"define.h"
#include "enums.h"
#include "func.h"
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
