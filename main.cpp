//
// Created by 11ale on 14.05.2024.
//
#include "Arkanoid.h"

int main()
{
    srand(time(NULL));
    //Window
    RenderWindow window(VideoMode(1920, 1080), "Arkanoid");

    //For work in program(parameters)
    bool GameWin = false;
    bool BossFight = false;
    bool GameOver = false;
    Vector2f pos;
    Clock clock, clockAnimation, clockAnimationMeteor, clockGenBullets, clockAliens, clockGenBulletsAlien, clockGenBulletsBoss;
    double time, timeGun, timeBackground, timeMeteor, timeAliens, timeGunAlien, timeBoss, timeGunBoss;

    //Background
    Texture textureSpace;
    textureSpace.loadFromFile("Image/cosmos.jpg");
    RectangleShape gameBackground(Vector2f(1920, 1080));
    gameBackground.setTexture(&textureSpace);
    RectangleShape gameBackground2(Vector2f(1920, 1080));
    gameBackground2.setTexture(&textureSpace);
    gameBackground2.setPosition(Vector2f(1920, 0));

    //Spaceship
    Vector2f moveRec;
    Texture texturePlayer;
    texturePlayer.loadFromFile("Image/main_boat.png");
    RectangleShape player(Vector2f(110, 110));
    player.setTexture(&texturePlayer);
    player.setPosition(Vector2f(100, 540));


    //Booooom player
    int countAnimBoom = 1;
    Texture pboom1Texture;
    pboom1Texture.loadFromFile("Image/pboom1.png");
    Texture pboom2Texture;
    pboom2Texture.loadFromFile("Image/pboom2.png");
    Texture pboom3Texture;
    pboom3Texture.loadFromFile("Image/pboom3.png");
    Texture pboom4Texture;
    pboom4Texture.loadFromFile("Image/pboom4.png");
    Texture pboom5Texture;
    pboom5Texture.loadFromFile("Image/pboom5.png");
    Texture pboom6Texture;
    pboom6Texture.loadFromFile("Image/pboom6.png");
    Texture pboom7Texture;
    pboom7Texture.loadFromFile("Image/pboom7.png");
    Sprite pboom;
    pboom.setTexture(pboom1Texture);

    //Meteors
    Texture meteorTexture1;
    meteorTexture1.loadFromFile("Image/meteor1.png");
    Texture meteorTexture3;
    meteorTexture3.loadFromFile("Image/meteor3.png");
    const int nmeteors = 10;
    Meteor meteors[nmeteors];
    int meteorType;
    for (int i = 0; i < nmeteors; i++){
        meteorType = 1 + rand() % 2;
        if (meteorType == 1) meteors[i].setTextureM(meteorTexture1);
        if (meteorType == 2) meteors[i].setTextureM(meteorTexture3);
    }

    //Player's score
    Text Score;
    Font Score_font;
    long scoreCount = 0;
    int countLvlUp = 1;
    Score_font.loadFromFile("Font/OffBit-Bold.ttf");
    Score.setFont(Score_font);
    Score.setFillColor(Color::White);
    Score.setCharacterSize(50);
    Score.setString("Score");
    Score.setPosition(1700, 50);
    Text ScorePoints;
    ScorePoints.setFont(Score_font);
    ScorePoints.setFillColor(Color::White);
    ScorePoints.setCharacterSize(40);
    ScorePoints.setString("00000");
    ScorePoints.setPosition(1698, 110);

    
    //Hp bar boss
    Text HpBarBoss;
    HpBarBoss.setFont(Score_font);
    HpBarBoss.setFillColor(Color::White);
    HpBarBoss.setCharacterSize(50);
    HpBarBoss.setString("15000/15000");
    HpBarBoss.setPosition(800, 100);
    int hpBarScore = 15000;

    
    //Text win
    Text Win;
    Win.setFont(Score_font);
    Win.setFillColor(Color::White);
    Win.setCharacterSize(200);
    Win.setString("You win!!!");
    Win.setPosition(600, 400);
    
    

    //Gun
    std::vector<Gun> guns;
    std::vector<Gun>::iterator itGun;
    int dmg = 1;
    int gunCount = 1;
    int lastIt = 0;
    int thisIt = 0;
    float gunUpScale_x = 30;
    float gunUpScale_y = 50;

    //Gun alien
    std::vector<Gun_alien> gunsAlien;
    std::vector<Gun_alien>::iterator itGunAlien;

    //Gun boss
    std::vector<Gun_boss> gunsBoss;
    std::vector<Gun_boss>::iterator itGunBoss;
    int lvlUpBoss = 0;


    //Animation jet stream
    int countAnim = 1;
    Texture herotexture1;
    herotexture1.loadFromFile("Image/fire1.png");
    Texture herotexture2;
    herotexture2.loadFromFile("Image/fire2.png");
    Texture herotexture3;
    herotexture3.loadFromFile("Image/fire3.png");
    Sprite herosprite;
    herosprite.setTexture(herotexture1);
    herosprite.setRotation(-90.f);

    //Alien
    Texture alienTexture;
    alienTexture.loadFromFile("Image/alien.png");
    std::vector <Alien*> aliens;
    std::vector <Alien*>::iterator itAliens;
    std::vector <int> directionAlien;
    std::vector <int>::iterator itDir;
    int upGenAlien = 7000; //timer Generation aliens in milliseconds

    //Alien Boss
    Texture bossAlienTexture;
    bossAlienTexture.loadFromFile("Image/boss_alien.png");
    Boss_alien bossAlien;
    bossAlien.setTextureM(bossAlienTexture);
    bool bossActivate = false;


    //Game
    while (window.isOpen())
    {
        Event event;
        time = clock.getElapsedTime().asMicroseconds();
        timeGunBoss = time / 3000;
        timeBoss = time / 3000;
        timeGunAlien = time / 3000;
        timeAliens = time / 3000;
        timeBackground = time / 6000;
        timeMeteor = time / 4000;
        timeGun = time / 3000;
        clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            //Player control
            switch (event.type) {
                case Event::KeyPressed:
                    if (event.key.code == Keyboard::S) moveRec.y = 0.1;
                    if (event.key.code == Keyboard::W) moveRec.y = -0.1;
                    if (event.key.code == Keyboard::A) moveRec.x = -0.1;
                    if (event.key.code == Keyboard::D) moveRec.x = 0.1;
                    break;
                case Event::KeyReleased:
                    if (event.key.code == Keyboard::S) moveRec.y = 0;
                    if (event.key.code == Keyboard::W) moveRec.y = 0;
                    if (event.key.code == Keyboard::A) moveRec.x = 0;
                    if (event.key.code == Keyboard::D) moveRec.x = 0;
                    break;
                default:
                    break;
            }
        }

        //End game
        if (GameOver){
            if (clockAnimationMeteor.getElapsedTime() > milliseconds(100)){
                clockAnimationMeteor.restart();
                herosprite.setPosition(-1000,-1000);
                for (int i = 0; i < guns.size(); i++){
                    for (int j = 0; j < guns[i].getBulletCount(); j++) guns[i].deleteBullet(j);
                    itGun = guns.begin()+i;
                    if (guns[i].getBulletCount() == 0) guns.erase(itGun);
                }
                for (int i = 0; i < gunsAlien.size(); i++){
                    for (int j = 0; j < gunsAlien[i].getBulletCount(); j++) gunsAlien[i].deleteBullet(j);
                    itGunAlien = gunsAlien.begin()+i;
                    if (gunsAlien[i].getBulletCount() == 0) gunsAlien.erase(itGunAlien);
                }
                for (int i = 0; i < aliens.size(); i++){
                    itAliens = aliens.begin()+i;
                    itDir = directionAlien.begin()+i;
                    aliens.erase(itAliens);
                    directionAlien.erase(itDir);
                }
                if (countAnimBoom == 1) {
                    pboom.setTexture(pboom1Texture);
                }
                if (countAnimBoom == 2) {
                    pboom.setTexture(pboom2Texture);
                }
                if (countAnimBoom == 3) {
                    pboom.setTexture(pboom3Texture);
                }
                if (countAnimBoom == 4) {
                    pboom.setTexture(pboom4Texture);
                }
                if (countAnimBoom == 5) {
                    pboom.setTexture(pboom5Texture);
                }
                if (countAnimBoom == 6) {
                    pboom.setTexture(pboom6Texture);
                }
                if (countAnimBoom == 7) {
                    pboom.setTexture(pboom7Texture);
                }
                countAnimBoom++;
                if (countAnimBoom > 8){
                    countAnimBoom = 1;
                    scoreCount = 0;
                    ScorePoints.setString("00000");
                    dmg = 1;
                    gunCount = 1;
                    gunUpScale_y = 50;
                    gunUpScale_x = 30;
                    countLvlUp = 1;
                    GameOver = false;
                    player.setPosition(Vector2f(100, 540));
                    for (int i = 0; i < nmeteors; i++) meteors[i].restart();
                }

            }
        }
        else if (BossFight){
            //Delete useless objects for boss fight
            for (int i = 0; i < gunsAlien.size(); i++){
                for (int j = 0; j < gunsAlien[i].getBulletCount(); j++) gunsAlien[i].deleteBullet(j);
                itGunAlien = gunsAlien.begin()+i;
                if (gunsAlien[i].getBulletCount() == 0) gunsAlien.erase(itGunAlien);
            }
            for (int i = 0; i < aliens.size(); i++){
                itAliens = aliens.begin()+i;
                itDir = directionAlien.begin()+i;
                aliens.erase(itAliens);
                directionAlien.erase(itDir);
            }
            for (int i = 0; i < nmeteors; i++){
                meteors[i].setBossFightPosition();
            }

            //Make boss
            if (bossActivate == false){
                bossActivate = true;
                bossAlien.restart();
            }


            //Make gun boss
            if (clockGenBulletsBoss.getElapsedTime() > milliseconds(2000)){
                clockGenBulletsBoss.restart();
                Gun_boss gunB1 = Gun_boss(1, 1, Vector2f(bossAlien.getPosition().x + 445, bossAlien.getPosition().y + 180));
                gunsBoss.push_back(gunB1);
                Gun_boss gunB2 = Gun_boss(1, 1, Vector2f(bossAlien.getPosition().x + 445, bossAlien.getPosition().y + 880));
                gunsBoss.push_back(gunB2);
                Gun_boss gunB3 = Gun_boss(1, 1, Vector2f(bossAlien.getPosition().x + 340, bossAlien.getPosition().y + 520));
                gunsBoss.push_back(gunB3);
                lvlUpBoss++;
                if (lvlUpBoss >= 30){
                    Gun_boss gunB4 = Gun_boss(1, 1, Vector2f(bossAlien.getPosition().x + 770, bossAlien.getPosition().y + 260));
                    gunsBoss.push_back(gunB4);
                    Gun_boss gunB5 = Gun_boss(1, 1, Vector2f(bossAlien.getPosition().x + 770, bossAlien.getPosition().y + 780));
                    gunsBoss.push_back(gunB5);
                }
            }

            //Move bullets boss
            for (int i = 0; i < gunsBoss.size(); i++){
                gunsBoss[i].move(timeGunBoss, player.getPosition());
                for (int j = 0; j < gunsBoss[i].getBulletCount(); j++){
                    if (gunsBoss[i].collision(player.getGlobalBounds(), j)){
                        gunsBoss[i].deleteBullet(j);
                        pboom.setPosition(player.getPosition().x, player.getPosition().y - 100);
                        herosprite.setPosition(-1000,-1000);
                        lvlUpBoss = 0;
                        BossFight = false;
                        GameOver = true;
                        break;
                    }
                }
                itGunBoss = gunsBoss.begin()+i;
                if (gunsBoss[i].getBulletCount() == 0) gunsBoss.erase(itGunBoss);
            }


            //Background animation
            gameBackground.move(-0.5 * timeBackground, 0);
            pos = gameBackground.getPosition();
            if (pos.x < -1920) gameBackground.setPosition(1920, pos.y);
            gameBackground2.move(-0.5 * timeBackground, 0);
            pos = gameBackground2.getPosition();
            if (pos.x < -1920) gameBackground2.setPosition(1920, pos.y);

            //Make gun
            if (clockGenBullets.getElapsedTime() > milliseconds(200)){
                clockGenBullets.restart();
                Gun gun = Gun(dmg, gunCount, Vector2f (player.getPosition().x + gunUpScale_x, player.getPosition().y + gunUpScale_y));
                guns.push_back(gun);
            }

            //Move bullets
            for (int i = 0; i < guns.size(); i++){
                guns[i].move(timeGun);
                for (int j = 0; j < guns[i].getBulletCount(); j++){
                    if (guns[i].collision(bossAlien.getGlobalBounds(), j)){
                        guns[i].deleteBullet(j);
                        if (bossAlien.getHp() - dmg <= 0) {
                            scoreCount = 99999;
                            hpBarScore = 0;
                            lvlUpBoss = 0;
                            ScorePoints.setString("99999");
                            bossActivate = false;
                            BossFight = false;
                            GameWin = true;
                        }
                        thisIt++;
                        hpBarScore -= dmg;
                        bossAlien.setHp(bossAlien.getHp() - dmg);
                    }
                }
                itGun = guns.begin()+i;
                if (guns[i].getBulletCount() == 0) guns.erase(itGun);
            }

            //Move boss
            bossAlien.move(timeBoss);
            if (bossAlien.collision(player.getGlobalBounds())){
                pboom.setPosition(player.getPosition().x, player.getPosition().y - 100);
                herosprite.setPosition(-1000,-1000);
                lvlUpBoss = 0;
                BossFight = false;
                GameOver = true;
                break;
            }

            //Animation jet stream
            if (clockAnimation.getElapsedTime() > milliseconds(100)) {
                clockAnimation.restart();
                if (countAnim == 1) {
                    herosprite.setTexture(herotexture1);
                }
                if (countAnim == 2) {
                    herosprite.setTexture(herotexture2);
                }
                if (countAnim == 3) {
                    herosprite.setTexture(herotexture3);
                }
                if (countAnim > 3) countAnim = 1;
                else countAnim++;
            }
            herosprite.setPosition(Vector2f(player.getPosition().x - 58, player.getPosition().y + 76));

            //Score and HpBar update
            if (lastIt != thisIt){
                lastIt = thisIt;
                int hpBarScoreCopy = hpBarScore;
                std::string hpBarStr = "";
                while (hpBarScoreCopy != 0){
                    if (hpBarScoreCopy % 10 == 0) hpBarStr+= "0";
                    if (hpBarScoreCopy % 10 == 1) hpBarStr+= "1";
                    if (hpBarScoreCopy % 10 == 2) hpBarStr+= "2";
                    if (hpBarScoreCopy % 10 == 3) hpBarStr+= "3";
                    if (hpBarScoreCopy % 10 == 4) hpBarStr+= "4";
                    if (hpBarScoreCopy % 10 == 5) hpBarStr+= "5";
                    if (hpBarScoreCopy % 10 == 6) hpBarStr+= "6";
                    if (hpBarScoreCopy % 10 == 7) hpBarStr+= "7";
                    if (hpBarScoreCopy % 10 == 8) hpBarStr+= "8";
                    if (hpBarScoreCopy % 10 == 9) hpBarStr+= "9";
                    hpBarScoreCopy /= 10;
                }
                std::reverse(hpBarStr.begin(), hpBarStr.end());
                HpBarBoss.setString(hpBarStr + "/15000");
            }

            //PlayerMove
            playerMove(player, moveRec);
        }
        else if(GameWin){
            if (clockAnimation.getElapsedTime() > milliseconds(500)){
                clockAnimation.restart();
                herosprite.setPosition(-1000,-1000);
                for (int i = 0; i < guns.size(); i++){
                    for (int j = 0; j < guns[i].getBulletCount(); j++) guns[i].deleteBullet(j);
                    itGun = guns.begin()+i;
                    if (guns[i].getBulletCount() == 0) guns.erase(itGun);
                }
                for (int i = 0; i < gunsAlien.size(); i++){
                    for (int j = 0; j < gunsAlien[i].getBulletCount(); j++) gunsAlien[i].deleteBullet(j);
                    itGunAlien = gunsAlien.begin()+i;
                    if (gunsAlien[i].getBulletCount() == 0) gunsAlien.erase(itGunAlien);
                }
                for (int i = 0; i < gunsBoss.size(); i++){
                    for (int j = 0; j < gunsBoss[i].getBulletCount(); j++) gunsBoss[i].deleteBullet(j);
                    itGunBoss = gunsBoss.begin()+i;
                    if (gunsBoss[i].getBulletCount() == 0) gunsBoss.erase(itGunBoss);
                }
                countAnimBoom++;
                if (countAnimBoom > 10){
                    pboom.setScale(0.5,0.5);
                    countAnimBoom = 1;
                    scoreCount = 0;
                    ScorePoints.setString("00000");
                    dmg = 1;
                    gunCount = 1;
                    gunUpScale_y = 50;
                    gunUpScale_x = 30;
                    countLvlUp = 1;
                    GameWin = false;
                    player.setPosition(Vector2f(100, 540));
                    for (int i = 0; i < nmeteors; i++) meteors[i].restart();
                }

            }
        }
        else {
            //Background animation
            gameBackground.move(-0.5 * timeBackground, 0);
            pos = gameBackground.getPosition();
            if (pos.x < -1920) gameBackground.setPosition(1920, pos.y);
            gameBackground2.move(-0.5 * timeBackground, 0);
            pos = gameBackground2.getPosition();
            if (pos.x < -1920) gameBackground2.setPosition(1920, pos.y);

            //Make Alien
            if (clockAliens.getElapsedTime() > milliseconds(upGenAlien)){
                clockAliens.restart();
                Alien* alien = new Alien;
                alien->setTextureM(alienTexture);
                aliens.push_back(alien);
                directionAlien.push_back(1);
            }


            //Make gun
            if (clockGenBullets.getElapsedTime() > milliseconds(300)){
                clockGenBullets.restart();
                Gun gun = Gun(dmg, gunCount, Vector2f (player.getPosition().x + gunUpScale_x, player.getPosition().y + gunUpScale_y));
                guns.push_back(gun);
            }

            //Make gun alien
            if (clockGenBulletsAlien.getElapsedTime() > milliseconds(5000)){
                clockGenBulletsAlien.restart();
                for (int i = 0; i < aliens.size(); i++) {
                    Gun_alien gunA = Gun_alien(1, 1, Vector2f(aliens[i]->getPosition().x + gunUpScale_x, aliens[i]->getPosition().y + gunUpScale_y));
                    gunsAlien.push_back(gunA);
                }
            }

            //Move Alien
            for (int i = 0; i < aliens.size(); i++){
                if (aliens[i]->getPosition_y() >= 970 || aliens[i]->getPosition_y() <= 200) directionAlien[i] *= -1;
                aliens[i]->move(timeAliens, directionAlien[i]);
                if (aliens[i]->collision(player.getGlobalBounds())){
                    pboom.setPosition(player.getPosition().x, player.getPosition().y - 100);
                    herosprite.setPosition(-1000,-1000);
                    GameOver = true;
                    break;
                }
            }

            //Move bullets
            for (int i = 0; i < guns.size(); i++){
                guns[i].move(timeGun);
                for (int j = 0; j < guns[i].getBulletCount(); j++){
                    for (int l = 0; l < nmeteors; l++) {
                        if (guns[i].collision(meteors[l].getGlobalBounds(), j)){
                            guns[i].deleteBullet(j);
                            if (meteors[l].getHp() - dmg <= 0) {
                                scoreCount += 100;
                                thisIt++;
                            }
                            meteors[l].setHp(meteors[l].getHp() - dmg);
                        }
                    }
                    for (int l = 0; l < aliens.size(); l++) {
                        if (guns[i].collision(aliens[l]->getGlobalBounds(), j)){
                            itAliens = aliens.begin()+l;
                            itDir = directionAlien.begin()+l;
                            guns[i].deleteBullet(j);
                            if (aliens[l]->getHp() - dmg <= 0) {
                                scoreCount += 200;
                                thisIt++;
//                                delete aliens[i];
                                aliens.erase(itAliens);
                                directionAlien.erase(itDir);
                            }
                            aliens[l]->setHp(aliens[l]->getHp() - dmg);
                        }
                    }
                }
                itGun = guns.begin()+i;
                if (guns[i].getBulletCount() == 0) guns.erase(itGun);
            }

            //Move bullets alien
            for (int i = 0; i < gunsAlien.size(); i++){
                gunsAlien[i].move(timeGunAlien);
                for (int j = 0; j < gunsAlien[i].getBulletCount(); j++){
                    if (gunsAlien[i].collision(player.getGlobalBounds(), j)){
                        gunsAlien[i].deleteBullet(j);
                        pboom.setPosition(player.getPosition().x, player.getPosition().y - 100);
                        herosprite.setPosition(-1000,-1000);
                        GameOver = true;
                        break;
                    }
                }
                itGunAlien = gunsAlien.begin()+i;
                if (gunsAlien[i].getBulletCount() == 0) gunsAlien.erase(itGunAlien);
            }

            //Score update
            if (lastIt != thisIt){
                lastIt = thisIt;
                int scoreCountCopy = scoreCount;
                int countZeros = 5;
                std::string scoreStr = "";
                std::string scoreStrZeroes = "";

                while (scoreCountCopy != 0){
                    countZeros--;
                    if (scoreCountCopy % 10 == 0) scoreStr+= "0";
                    if (scoreCountCopy % 10 == 1) scoreStr+= "1";
                    if (scoreCountCopy % 10 == 2) scoreStr+= "2";
                    if (scoreCountCopy % 10 == 3) scoreStr+= "3";
                    if (scoreCountCopy % 10 == 4) scoreStr+= "4";
                    if (scoreCountCopy % 10 == 5) scoreStr+= "5";
                    if (scoreCountCopy % 10 == 6) scoreStr+= "6";
                    if (scoreCountCopy % 10 == 7) scoreStr+= "7";
                    if (scoreCountCopy % 10 == 8) scoreStr+= "8";
                    if (scoreCountCopy % 10 == 9) scoreStr+= "9";
                    scoreCountCopy /= 10;
                }
                std::reverse(scoreStr.begin(), scoreStr.end());
                for (int i = 0; i < countZeros; i++) scoreStrZeroes += "0";
                ScorePoints.setString(scoreStrZeroes + scoreStr);
            }

            //Lvl up
            if (scoreCount >= 99999) GameOver = true;
            else if (scoreCount >= 50000  && countLvlUp == 6){
                BossFight = true;
                countLvlUp++;
            }
            else if (scoreCount >= 15000  && countLvlUp == 5){
                gunCount++;
                upGenAlien -= 1500;
                countLvlUp++;
                gunUpScale_y -= 7;
            }
            else if (scoreCount >= 5000  && countLvlUp == 4){
                dmg++;
                gunCount++;
                upGenAlien -= 1500;
                countLvlUp++;
                gunUpScale_y -= 7;
            }
            else if (scoreCount >= 2000 && countLvlUp == 3){
                dmg++;
                upGenAlien -= 1500;
                gunCount++;
                countLvlUp++;
                gunUpScale_y -= 7;
            }
            else if (scoreCount >= 1000 && countLvlUp == 2){
                gunCount++;
                upGenAlien -= 1000;
                gunUpScale_y -= 7;
                countLvlUp++;
            }
            else if (scoreCount >= 500 && countLvlUp == 1){
                gunCount++;
                upGenAlien -= 1000;
                countLvlUp++;
            }


            //Animation jet stream
            if (clockAnimation.getElapsedTime() > milliseconds(100)) {
                clockAnimation.restart();
                if (countAnim == 1) {
                    herosprite.setTexture(herotexture1);
                }
                if (countAnim == 2) {
                    herosprite.setTexture(herotexture2);
                }
                if (countAnim == 3) {
                    herosprite.setTexture(herotexture3);
                }
                if (countAnim > 3) countAnim = 1;
                else countAnim++;
            }
            herosprite.setPosition(Vector2f(player.getPosition().x - 58, player.getPosition().y + 76));

            //Move meteor
            for (int i = 0; i < nmeteors; i++) {
                meteors[i].move(timeMeteor);
                if (meteors[i].collision(player.getGlobalBounds())){
                    pboom.setPosition(player.getPosition().x, player.getPosition().y - 100);
                    herosprite.setPosition(-1000,-1000);
                    GameOver = true;
                    break;
                }
            }

            //PlayerMove
            playerMove(player, moveRec);
        }

        //Work with window
        window.clear();
        window.draw(gameBackground2);
        window.draw(gameBackground);
        window.draw(herosprite);
        for (int i = 0; i < guns.size(); i++) guns[i].draw(window);
        for (int i = 0; i < gunsAlien.size(); i++) gunsAlien[i].draw(window);
        for (int i = 0; i < nmeteors; i++) meteors[i].draw(window);
        for (int i = 0; i < aliens.size(); i++) aliens[i]->draw(window);
        if (GameOver) window.draw(pboom); else window.draw(player);
        if (BossFight){
            bossAlien.draw(window);
            for (int i = 0; i < gunsBoss.size(); i++) gunsBoss[i].draw(window);
            window.draw(HpBarBoss);
        }
        window.draw(Score);
        window.draw(ScorePoints);
        if (GameWin) window.draw(Win);
        window.display();
    }

    return EXIT_SUCCESS;
}
