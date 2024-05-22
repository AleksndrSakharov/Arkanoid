//
// Created by 11ale on 21.05.2024.
//
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
using namespace sf;


class Gun {
protected:
    std::vector<RectangleShape> _bullet;
    int _dmg;
    int _gunCount;
public:
    Gun();
    Gun(int dmg, int gunCount, Vector2f pos);
    ~Gun();
    void deleteBullet(int i);
    int getBulletCount();
    void move(double& time);
    void draw(RenderWindow& window);
    bool collision(FloatRect object, int i);
    FloatRect getBulletBounds(int j); //Position in global coordinates
};
