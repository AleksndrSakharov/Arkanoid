//
// Created by 11ale on 20.05.2024.
//

#include "Alien.h"

void Alien::setHp(int hp) {
    _hp = hp;
}

void Alien::move(double &time, int direction) {
    _SpaceObject.move(static_cast<float>(-0.5*time), static_cast<float>(0.2*direction*time));
    if (_SpaceObject.getPosition().x < -100) restart();
}

void Alien::setTextureM(sf::Texture &texture1) {
    _TextureObject = texture1;
    _SpaceObject.setSize({static_cast<float>(_TextureObject.getSize().x), static_cast<float>(_TextureObject.getSize().y)});
    _SpaceObject.setTexture(&_TextureObject);
    _SpaceObject.setRotation(-90.f);
    restart();
}

float Alien::getPosition_y() {
    return _SpaceObject.getPosition().y;
}

void Alien::restart() {
    _hp = 15;
    float x1 = static_cast<float>(rand() % 400 + 1920);
    float y1 = static_cast<float>(200 + rand() % 760);
    _SpaceObject.setPosition(Vector2f(x1, y1));
    _SpaceObject.setScale(0.35, 0.35);
}

Vector2f Alien::getPosition() {
    return _SpaceObject.getPosition();
}
