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
        _bullet[i].setPosition(Vector2f(100, 540));
    }
}
void Gun::lvlUp(int dmg, int gunCount) {
    RectangleShape bullet;
    _dmg = dmg;
    if (gunCount < 5)
    _gunCount = gunCount;
    for (int i = 0; i < _gunCount; i++) {
        _bullet.push_back(bullet);
        _bullet[i].setSize(Vector2f(10, 4));
        _bullet[i].setFillColor(Color::White);
    }
}

bool Gun::collision(sf::FloatRect object) {
    for (int i = 0; i < _bullet.size(); i++)
        if (_bullet[i].getGlobalBounds().intersects(object)) return true;
    return false;
}

void Gun::move(double &time) {
    std::vector<RectangleShape>::iterator it;
    for (int i = 0; i < _gunCount; i++) {
        it = _bullet.begin()+i;
        _bullet[i].move(static_cast<float>(2*time), 0);
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