//
// Created by 11ale on 26.05.2024.
//

#include "Boss_alien.h"

Boss_alien::Boss_alien() {
    _TextureObject.loadFromFile("Image/boss_alien.png");
    _SpaceObject.setTexture(_TextureObject);
    _hp = 10000;
}

int Boss_alien::getHp() {
    return _hp;
}

bool Boss_alien::collision(sf::FloatRect object) {
    if (_SpaceObject.getGlobalBounds().intersects(object)) return true;
    return false;
}

FloatRect Boss_alien::getGlobalBounds() {
    return _SpaceObject.getGlobalBounds();
}

void Boss_alien::draw(sf::RenderWindow &window) {
    window.draw(_SpaceObject);
}

void Boss_alien::setHp(int hp) {
    _hp = hp;
}

Vector2f Boss_alien::getPosition() {
    return _SpaceObject.getPosition();
}

void Boss_alien::move(double &time) {
    if (_SpaceObject.getPosition().x >= 1000)
    _SpaceObject.move(static_cast<float>(-0.5*time), 0);
}

void Boss_alien::setTextureM(sf::Texture &texture1) {
    _TextureObject = texture1;
    _SpaceObject.setTexture(_TextureObject);
    _SpaceObject.setPosition(4000, 4000);
}

void Boss_alien::restart() {
    _hp = 10000;
    float x1 = static_cast<float>(2000);
    float y1 = static_cast<float>(950);
    _SpaceObject.setPosition(Vector2f(x1, y1));
    _SpaceObject.setRotation(-90.f);
    _SpaceObject.setScale(2, 2);
}
