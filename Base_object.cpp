//
// Created by 11ale on 20.05.2024.
//
#include "Base_object.h"

int Base_object::getHp() {
    return _hp;
}

void Base_object::setHp(int hp){
    _hp = hp;
    if (hp <= 0)
    restart();
}

void Base_object::setTextureM(Texture& texture1){
    _TextureObject = texture1;
    _SpaceObject.setSize({static_cast<float>(_TextureObject.getSize().x), static_cast<float>(_TextureObject.getSize().y)});
    _SpaceObject.setTexture(&_TextureObject);
}

void Base_object::move(double& time){
    _SpaceObject.move(static_cast<float>(-0.9*time), 0);
    if (_SpaceObject.getPosition().x < -100) restart();
}

Base_object::Base_object(){
    _TextureObject.loadFromFile("Image/meteor1.png");
    _SpaceObject.setSize({455,269});
    _SpaceObject.setTexture(&_TextureObject);
    _hp = 10;
    restart();
}
Base_object::~Base_object(){

}

void Base_object::draw(RenderWindow& window){
    window.draw(_SpaceObject);
}
bool Base_object::collision(FloatRect object){
    if (_SpaceObject.getGlobalBounds().intersects(object)) return true;
    return false;
}
void Base_object::restart(){
    _hp = 10;
    float x1 = static_cast<float>(rand() % 1920 + 1920);
    float y1 = static_cast<float>(rand() % 970);
    _SpaceObject.setPosition(Vector2f(x1, y1));
    _SpaceObject.setScale(0.35, 0.35);

}
FloatRect Base_object::getGlobalBounds(){
    return _SpaceObject.getGlobalBounds();
}