//
// Created by 11ale on 26.05.2024.
//

#include "Gun_alien.h"


class Gun_boss : public Gun{
protected:
public:
    Gun_boss();
    Gun_boss(int dmg, int gunCount, Vector2f pos);
    void move(double& time, Vector2f pos);
};
