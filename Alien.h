//
// Created by 11ale on 20.05.2024.
//
#pragma once
#include "Base_object.h"

class Alien : public Base_object{
public:
    void setHp(int hp);
    void move(double& time, int direction);
    void setTextureM(Texture& texture1);
    Vector2f getPosition();
    float getPosition_y();
    void restart();
};



