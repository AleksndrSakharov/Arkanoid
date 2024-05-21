//
// Created by 11ale on 14.05.2024.
//
#include "Arkanoid.h"

int main()
{
    srand(time(NULL));
    //Window
    RenderWindow window(VideoMode(1920, 1080), "Arkanoid");

    //Background
    Texture textureSpace;
    textureSpace.loadFromFile("Image/cosmos.jpg");
    RectangleShape gameBackground(Vector2f(1920, 1080));
    gameBackground.setTexture(&textureSpace);
    RectangleShape gameBackground2(Vector2f(1920, 1080));
    gameBackground2.setTexture(&textureSpace);
    gameBackground2.setPosition(Vector2f(1920, 0));

    //For work in program(parameters)
    bool GameOver = false;
    Vector2f pos;
    Clock clock, clockAnimation, clockAnimationMeteor;
    double time, timePlayer, timeBackground, timeMeteor;

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
    Score_font.loadFromFile("Font/OffBit-Bold.ttf");
    Score.setFont(Score_font);
    Score.setFillColor(Color::White);
    Score.setCharacterSize(50);
    Score.setString("Score");
    Score.setPosition(1800, 50);
    Text ScorePoints;
    Font ScorePoints_font;
    ScorePoints.setFont(Score_font);
    ScorePoints.setFillColor(Color::White);
    ScorePoints.setCharacterSize(30);
    ScorePoints.setString("00000");
    ScorePoints.setPosition(1780, 90);
    
    

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
//        timePlayer = time / 3000;
        clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            //Player control
            switch (event.type) {
                case Event::KeyPressed:
                    if (event.key.code == Keyboard::S) moveRec.y = 0.1;
                    if (event.key.code == Keyboard::W) moveRec.y = -0.1 ;
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


            //Animation jet stream
            if (clockAnimation.getElapsedTime() > milliseconds(100)) {
                clockAnimation.restart();
                if (countAnim == 1) {
                    herosprite.setTexture(herotexture1);
//                herosprite.setRotation(45.f);
                }
                if (countAnim == 2) {
                    herosprite.setTexture(herotexture2);
//                herosprite.setRotation(45.f);
                }
                if (countAnim == 3) {
                    herosprite.setTexture(herotexture3);
//                herosprite.setRotation(45.f);
                }
                if (countAnim > 3) countAnim = 1;
                else countAnim++;
            }
            herosprite.setPosition(Vector2f(player.getPosition().x - 58, player.getPosition().y + 76));


            //Background animation
            gameBackground.move(-0.5 * timeBackground, 0);
            pos = gameBackground.getPosition();
            if (pos.x < -1920) gameBackground.setPosition(1920, pos.y);
            gameBackground2.move(-0.5 * timeBackground, 0);
            pos = gameBackground2.getPosition();
            if (pos.x < -1920) gameBackground2.setPosition(1920, pos.y);

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
        for (int i = 0; i < nmeteors; i++) meteors[i].draw(window);
        if (GameOver) window.draw(pboom); else window.draw(player);
        window.draw(herosprite);
        window.draw(Score);
        window.display();
    }

    return EXIT_SUCCESS;
}
