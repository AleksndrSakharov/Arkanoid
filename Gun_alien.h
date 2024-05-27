//
// Created by UnityTester on 27.05.2024.
//
#include "Gun.h"



class Gun_alien : public Gun{
public:
    Gun_alien(int dmg, int gunCount, Vector2f pos);
    void move(double& time);
};


