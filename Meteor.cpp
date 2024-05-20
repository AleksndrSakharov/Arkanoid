//
// Created by 11ale on 18.05.2024.
//

#include "Meteor.h"

void Meteor::setTextureM(Texture& texture1){
    _TextureObject = texture1;
    _SpaceObject.setSize({static_cast<float>(_TextureObject.getSize().x), static_cast<float>(_TextureObject.getSize().y)});
    _SpaceObject.setTexture(&_TextureObject);
}

void Meteor::move(double& time){
    _SpaceObject.move(static_cast<float>(-0.9*time), 0);
    if (_SpaceObject.getPosition().x < -100) restart();
}

Meteor::Meteor(){
    _TextureObject.loadFromFile("Image/meteor1.png");
    _SpaceObject.setSize({455,269});
    _SpaceObject.setTexture(&_TextureObject);
    restart();
}
Meteor::~Meteor(){

}

void Meteor::draw(RenderWindow& window){
    window.draw(_SpaceObject);
}
bool Meteor::collision(FloatRect object){
    if (_SpaceObject.getGlobalBounds().intersects(object)) return true;
    return false;
}
void Meteor::restart(){
    float x1 = static_cast<float>(rand() % 1920 + 1920);
    float y1 = static_cast<float>(rand() % 970);
    _SpaceObject.setPosition(Vector2f(x1, y1));
    _SpaceObject.setScale(0.35, 0.35);

}
FloatRect Meteor::getMeteorBounds(){
    return _SpaceObject.getGlobalBounds();
}