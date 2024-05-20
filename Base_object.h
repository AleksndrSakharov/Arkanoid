//
// Created by 11ale on 20.05.2024.
//
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;



class Base_object {
protected:
    RectangleShape _SpaceObject;
    Texture _TextureObject;
public:
    Base_object();
    ~Base_object();

    virtual void setTextureM(Texture& texture1);
    virtual void move(double& time);
    virtual void draw(RenderWindow& window);
    virtual bool collision(FloatRect object);
    virtual void restart(); //Set new coords
    virtual FloatRect getMeteorBounds(); //Position in global coordinates
};