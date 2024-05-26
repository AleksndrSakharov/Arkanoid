//
// Created by 11ale on 26.05.2024.
//
#pragma once
#include <SFML/Graphics.hpp>
#include "Base_object.h"
using namespace sf;

class Boss_alien{
protected:
    int _hp;
    Sprite _SpaceObject;
    Texture _TextureObject;
public:
    Boss_alien();
    int getHp();
    void setHp(int hp);
    void move(double& time);
    bool collision(FloatRect object);
    void draw(RenderWindow& window);
    FloatRect getGlobalBounds(); //Position in global coordinates
    void setTextureM(Texture& texture1);
    Vector2f getPosition();
    void restart();
};

