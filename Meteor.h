//
// Created by 11ale on 18.05.2024.
//
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;



class Meteor {
private:
    RectangleShape _SpaceObject;
    Texture _TextureObject;
public:
    Meteor();
    ~Meteor();

    void setTextureM(Texture& texture1);
    void move(double& time);
    void draw(RenderWindow& window);
    bool collision(FloatRect object);
    void restart(); //Set new coords
    FloatRect getMeteorBounds(); //Position in global coordinates
};

