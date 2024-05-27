//
// Created by UnityTester on 27.05.2024.
//

#include "Gun_alien.h"

Gun_alien::Gun_alien(int dmg, int gunCount, Vector2f pos) {
    RectangleShape bullet;
    float posDelta = 0;
    _dmg = dmg;
    _gunCount = gunCount;
    for (int i = 0; i < _gunCount; i++) {
        _bullet.push_back(bullet);
        _bullet[i].setSize(Vector2f(10, 4));
        _bullet[i].setFillColor(Color::Red);
        _bullet[i].setPosition(Vector2f (pos.x, pos.y - 185 + posDelta));
        posDelta += 10;
    }
}


void Gun_alien::move(double &time) {
    std::vector<RectangleShape>::iterator it;
    for (int i = 0; i < _bullet.size(); i++) {
        it = _bullet.begin()+i;
        _bullet[i].move(static_cast<float>(-2*time), 0);
        if (_bullet[i].getPosition().x >= 1940) _bullet.erase(it);
    }
}

