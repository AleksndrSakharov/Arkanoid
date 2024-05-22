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
    bool GameOver = false;
    Vector2f pos;
    Clock clock, clockAnimation, clockAnimationMeteor, clockGenBullets;
    double time, timeGun, timeBackground, timeMeteor;

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
//    Texture meteorTexture2;
//    meteorTexture2.loadFromFile("Image/meteor2.png");
    Texture meteorTexture3;
    meteorTexture3.loadFromFile("Image/meteor3.png");
    const int nmeteors = 10;
    Meteor meteors[nmeteors];
    int meteorType;
    for (int i = 0; i < nmeteors; i++){
        meteorType = 1 + rand() % 2;
        if (meteorType == 1) meteors[i].setTextureM(meteorTexture1);
//        if (meteorType == 2) meteors[i].setTextureM(meteorTexture2);
        if (meteorType == 2) meteors[i].setTextureM(meteorTexture3);
    }

    //Player's score
    Text Score;
    Font Score_font;
    long scoreCount = 0;
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


    //Gun
    std::vector<Gun> guns;
    std::vector<Gun>::iterator itGun;
    int dmg = 1;
    int gunCount = 2;


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

    //Game
    while (window.isOpen())
    {
        Event event;
        time = clock.getElapsedTime().asMicroseconds();
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
                    if (event.key.code == Keyboard::S) moveRec.y = 0.3;
                    if (event.key.code == Keyboard::W) moveRec.y = -0.3 ;
                    if (event.key.code == Keyboard::A) moveRec.x = -0.3;
                    if (event.key.code == Keyboard::D) moveRec.x = 0.3;
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
                ScorePoints.setString("00000");
                for (int i = 0; i < guns.size(); i++){
                    for (int j = 0; j < guns[i].getBulletCount(); j++) guns[i].deleteBullet(j);
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
                    GameOver = false;
                    player.setPosition(Vector2f(100, 540));
                    for (int i = 0; i < nmeteors; i++) meteors[i].restart();
                }

            }
        }else {
            //Background animation
            gameBackground.move(-0.5 * timeBackground, 0);
            pos = gameBackground.getPosition();
            if (pos.x < -1920) gameBackground.setPosition(1920, pos.y);
            gameBackground2.move(-0.5 * timeBackground, 0);
            pos = gameBackground2.getPosition();
            if (pos.x < -1920) gameBackground2.setPosition(1920, pos.y);

            //Make gun
            Gun gun = Gun(dmg, gunCount, Vector2f (player.getPosition().x + 30, player.getPosition().y + 50));
            if (clockGenBullets.getElapsedTime() > milliseconds(200)){
                clockGenBullets.restart();
                guns.push_back(gun);
            }

            //Move bullets
            for (int i = 0; i < guns.size(); i++){
                guns[i].move(timeGun);
                for (int j = 0; j < guns[i].getBulletCount(); j++){
                    for (int l = 0; l < nmeteors; l++) {
                        if (guns[i].collision(meteors[l].getGlobalBounds(), j)){
                            if (meteors[l].getHp() - dmg == 0) scoreCount += 100;
                            meteors[l].setHp(meteors[l].getHp() - dmg);
                            guns[i].deleteBullet(j);
                        }
                    }
                }
                itGun = guns.begin()+i;
                if (guns[i].getBulletCount() == 0) guns.erase(itGun);
            }

            //Score update
            int scoreCountCopy = scoreCount;
            int countZeros = 5;
            std::string scoreStr = "";
//            std::cout << scoreCount << std::endl;
            std::string scoreStrZeroes = "";
            while (scoreCountCopy >= 1){
                countZeros--;
                switch (scoreCountCopy % 10) {
                    case 1:
                        scoreStr += "1";
                    case 2:
                        scoreStr += "2";
                    case 3:
                        scoreStr += "3";
                    case 4:
                        scoreStr += "4";
                    case 5:
                        scoreStr += "5";
                    case 6:
                        scoreStr += "6";
                    case 7:
                        scoreStr += "7";
                    case 8:
                        scoreStr += "8";
                    case 9:
                        scoreStr += "9";
                    case 0:
                        scoreStr += "0";
                }
                scoreCountCopy /= 10;
            }

            for (int i = 0; i < countZeros; i++) scoreStrZeroes += "0";
            std::cout << scoreStrZeroes + scoreStr << std::endl;
            ScorePoints.setString(scoreStrZeroes + scoreStr);

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
                    GameOver = true;
                    pboom.setPosition(player.getPosition().x, player.getPosition().y - 100);
                    herosprite.setPosition(-1000,-1000);
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
        for (int i = 0; i < guns.size(); i++) guns[i].draw(window);
        for (int i = 0; i < nmeteors; i++) meteors[i].draw(window);
        if (GameOver) window.draw(pboom); else window.draw(player);
        window.draw(herosprite);
        window.draw(Score);
        window.draw(ScorePoints);
        window.display();
    }

    return EXIT_SUCCESS;
}
