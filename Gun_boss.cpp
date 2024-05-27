//
// Created by 11ale on 26.05.2024.
//

#include "Gun_boss.h"

Gun_boss::Gun_boss() {
    RectangleShape bullet;
    _dmg = 1;
    _gunCount = 1;
    for (int i = 0; i < _gunCount; i++) {
        _bullet.push_back(bullet);
        _bullet[i].setSize(Vector2f(10, 10));
        _bullet[i].setFillColor(Color::Red);
        _bullet[i].setPosition(Vector2f (0, 0));
    }
}

Gun_boss::Gun_boss(int dmg, int gunCount, Vector2f pos) {
    RectangleShape bullet;
    float posDelta = 0;
    _dmg = dmg;
    _gunCount = gunCount;
    for (int i = 0; i < _gunCount; i++) {
        _bullet.push_back(bullet);
        _bullet[i].setSize(Vector2f(10, 10));
        _bullet[i].setFillColor(Color::Red);
        _bullet[i].setPosition(Vector2f (pos.x, pos.y - 940 + posDelta));
        posDelta += 10;
    }
}

void Gun_boss::move(double &time, Vector2f pos) {
    std::vector<RectangleShape>::iterator it;
    for (int i = 0; i < _bullet.size(); i++) {
        it = _bullet.begin()+i;
        if (_bullet[i].getPosition().y < pos.y + 17) _bullet[i].move(static_cast<float>(-0.75*time), static_cast<float>(0.2 * time));
        else _bullet[i].move(static_cast<float>(-0.75*time), static_cast<float>(-0.2 * time));
        if (_bullet[i].getPosition().x < -100) _bullet.erase(it);
    }
}