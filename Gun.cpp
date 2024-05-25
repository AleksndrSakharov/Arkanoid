//
// Created by 11ale on 21.05.2024.
//

#include "Gun.h"

Gun::Gun() {
    RectangleShape bullet;
    _dmg = 1;
    _gunCount = 2;
    for (int i = 0; i < _gunCount; i++) {
        _bullet.push_back(bullet);
        _bullet[i].setSize(Vector2f(10, 4));
        _bullet[i].setFillColor(Color::White);
        _bullet[i].setPosition(Vector2f(0, 0));
    }
}

Gun::Gun(int dmg, int gunCount, Vector2f pos) {
    RectangleShape bullet;
    float posDelta = 0;
    _dmg = dmg;
    _gunCount = gunCount;
    for (int i = 0; i < _gunCount; i++) {
        _bullet.push_back(bullet);
        _bullet[i].setSize(Vector2f(10, 4));
        _bullet[i].setFillColor(Color::White);
        _bullet[i].setPosition(Vector2f (pos.x, pos.y + posDelta));
        posDelta += 10;
    }
}

int Gun::getBulletCount() {
    return _bullet.size();
}

void Gun::deleteBullet(int i) {
    std::vector<RectangleShape>::iterator it;
    it = _bullet.begin()+i;
    _bullet.erase(it);
}


bool Gun::collision(sf::FloatRect object, int i) {
    if (_bullet[i].getGlobalBounds().intersects(object)) return true;
    return false;
}

void Gun::move(double &time) {
    std::vector<RectangleShape>::iterator it;
    for (int i = 0; i < _bullet.size(); i++) {
        it = _bullet.begin()+i;
        _bullet[i].move(static_cast<float>(3*time), 0);
        if (_bullet[i].getPosition().x > 2000) _bullet.erase(it);
    }
}

FloatRect Gun::getBulletBounds(int j) {
    return _bullet[j].getGlobalBounds();
}

void Gun::draw(sf::RenderWindow &window) {
    for (int i = 0; i < _bullet.size(); i++)
        window.draw(_bullet[i]);
}

Gun::~Gun() {

}