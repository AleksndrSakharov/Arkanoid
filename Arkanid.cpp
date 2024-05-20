//
// Created by 11ale on 18.05.2024.
//
#include "Arkanoid.h"
void playerMove(RectangleShape& player, Vector2f& moveRec){
    //Move player
    player.move(moveRec);
    Vector2f pos = player.getPosition();
    if (pos.x > 1700) player.setPosition(1700, pos.y);
    if (pos.x < 30) player.setPosition(30, pos.y);
    if (pos.y > 970) player.setPosition(pos.x, 970);
    if (pos.y < 0) player.setPosition(pos.x, 0);
    if (pos.x > 1700 && pos.y < 0) player.setPosition(1700, 0);
    if (pos.x > 1700 && pos.y > 970) player.setPosition(1700, 970);
    if (pos.x < 30 && pos.y < 0) player.setPosition(30, 0);
    if (pos.x < 30 && pos.y > 970) player.setPosition(30, 970);
}

