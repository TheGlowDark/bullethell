#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.cpp"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <windows.h>
#include "string.h"
#include <sstream>


int getrandom(int max, int min) {
    int num = min + rand() % (max - min + 1);
    return num;
}


int getrandom(int max, int min, float x) {
    int num = min + rand() % (max - min + 1);
    while (abs(x - num) < 100) {
        num = min + rand() % (max - min + 1);
    }
    return num;
}




sf::Vector2f playerpath(player p, int a) {
    sf::Vector2f r(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and (p.position().x + 600 * 0.3 - 85 < a))
        r.x = 6;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and (p.position().x) > 0)
        r.x = -6;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        r.y = -6;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        r.y = 6;
    return r;
}

void teleportcheck(player& p, int a, int b) {
 //   if (p.position().x < -120) { 
 //       p.setx(-119);
 //   }
    if (p.position().y < -60) {
        p.sety(b - 60);
    }
  //  else if (p.position().x + 600 * 0.3 > a) {  
  //      p.setx(p.position().x + 600 * 0.3);
 //   }
    else if (p.position().y > b - 59) { 
        p.sety(-59);
    }
}


bool checkcollusion(sf::FloatRect rec1, sf::FloatRect rec2) {
    return (rec1.left + rec1.width > rec2.left and rec1.left < rec2.left + rec2.width and rec2.top + rec2.height > rec1.top and rec1.top + rec1.height > rec2.top);
}



//void createbin(std::ifstream& txt, std::ofstream& bin) {
//    while (!txt.eof()) {
//        int s;
//        txt >> s;
//        bin.write((char*)&s, sizeof(s));
//    }
//
//}


void readb(std::ifstream& lb, int& s) {
    if(lb)
     lb.read((char*)&s, sizeof(s));
    //return 0;
}




int main()
{
    int wx = 1000, wy = 800;
    sf::RenderWindow window(sf::VideoMode(wx, wy), "Bullet_hell",(sf::Style::Titlebar, sf::Style::Close));
    sf::Texture field;
    field.loadFromFile("assets/textures/field.png");
    sf::Sprite fieldspr;
    fieldspr.setTexture(field);
    window.draw(fieldspr);

    //sf::RectangleShape rectangle(sf::Vector2f(100, 100)); ));
    std::string texturep =  "assets/textures/fox.png";
    std::string texturepleft = "assets/textures/runleft.png";
    std::string texturepright = "assets/textures/runright.png";
    std::string texturec = "assets/textures/coin.png"; //--------------дописать
    std::string textureb = "assets/textures/bullet.png";

    sf::Vector2f temp(1600, 1600);
    player player1(temp, texturepleft, texturepright, texturep);


    sf::Vector2f ab(40, 40);
    float speed1 = 12;
   // bullet bullet1(textureb, ab, speed1);
    sf::Texture btexture;

    //затемненный экран---------------------------------------------
    sf::RectangleShape blackscreen;
    blackscreen.setFillColor(sf::Color(0, 0, 0, 150));
    blackscreen.setSize(sf::Vector2f(1001, 801));


    //спрайт для отрисовки монет-------------------------
    sf::Sprite coing;
    sf::Texture ctexture;
    ctexture.loadFromFile(texturec);
    coing.setTexture(ctexture);
    coing.setScale(0.2, 0.2);


    //music---------------------------------------
    sf::SoundBuffer theme, pauseon, pauseoff, themedeath, themecoin, themelevel;
    theme.loadFromFile("assets/sfx/gametheme2.wav");
    pauseon.loadFromFile("assets/sfx/pauseon.wav");
    pauseoff.loadFromFile("assets/sfx/pauseoff.wav");
    themedeath.loadFromFile("assets/sfx/death.wav");
    themecoin.loadFromFile("assets/sfx/coin.wav");
    themelevel.loadFromFile("assets/sfx/level.wav");
    sf::Sound gametheme, gamedeath, gamecoin, gamelevel, pon ,poff;
    gametheme.setBuffer(theme);
    gamedeath.setBuffer(themedeath);
    gamecoin.setBuffer(themecoin);
    gamelevel.setBuffer(themelevel);
    pon.setBuffer(pauseon);
    poff.setBuffer(pauseoff);


    gamecoin.setVolume(60);
    gametheme.setVolume(30);




    //проверка на нажатие вне окна----------------------------------------



    //-----------------------------------------

    //bul используется для отрисовки всех пуль---------------------------------------------------------
    sf::Sprite bul;
    btexture.loadFromFile(textureb);
    bul.setTexture(btexture);

    bul.setScale(0.3, 0.3);

    //текст-----------------------------------------
    sf::Font font;
    font.loadFromFile("assets/font/1.TTF");

    sf::String A = "score ";
    sf::Text score;
    score.setFont(font);

    sf::String L = "You are dead!";
    sf::Text textlose;
    textlose.setFont(font);
    textlose.setString(L);

    textlose.setPosition(200, 300);
    textlose.setCharacterSize(100);

    score.setPosition(50, 0);
    score.setCharacterSize(70);


    sf::String H = "Highscore ";
    sf::Text htext;
    htext.setFont(font);
    htext.setString(H);
    htext.setPosition(550, 400);
    htext.setCharacterSize(30);

    sf::String LVL = "level ";
    sf::Text lvltext;
    lvltext.setFont(font);
    lvltext.setString(LVL);
    lvltext.setPosition(55, 60);
    lvltext.setCharacterSize(40);


    sf::String P = "||";
    sf::Text ptext;
    ptext.setFont(font);
    ptext.setString(P);
    ptext.setCharacterSize(100);
    ptext.setPosition(450, 350);

    //int k = 0;
    //if (!out) {
    //    out.write((char*)&k, sizeof k);
    //}
    //inbin.read((char*)&k, sizeof k);
    //outt << k;

    bool game = true;
    



    window.setFramerateLimit(60);
    //bullet1.spawn(50);
    do {
        game = true;
        int sc = 0;
        std::ifstream inbin("info.bin", std::ios::binary);
     //   std::ifstream intxt("info.txt");
        int highscore;
        readb(inbin, highscore);
        inbin.close();
        //inbin.write((char*)&highscore, sizeof(highscore));
      //  outtxt << highscore;
        //inbin.close();
       // std::ofstream out("info.bin");

        gametheme.play();
        gametheme.setLoop(true);

        std::vector<class bullet> gamebullets;

        std::vector<class coin> gamecoins;

        lvltext.setString(LVL + '1');
        score.setString(A + '0');
        player1.getstart();
        int j = 0, m = 0, s = 0, c = 0, ccount = 0, difficultcount = 0, difficult = 20, lvlcount = 1;
        bool alive = true ,mpressed = false, pause = false;
        while (window.isOpen())
        {
            if (alive == true and !pause) {
                s++;
                m++;
                j++;   //счетчик для генерации пуль
                if (ccount != 3) {
                    c++;
                }
                if (difficult > 6) {
                    difficultcount++;
                }
                if (difficultcount == 900) {
                    difficult = difficult - 2;
                    difficultcount = 0;
                    j = 0;
                    lvlcount++;
                    std::ostringstream level;
                    level << lvlcount;
                    lvltext.setString(LVL + level.str());
                    gamelevel.play();
                }

                if (j == difficult) {
                    int l = getrandom(800, 0);
                    //bullet bullet1 = new bullet(textureb, speed1);
                    bullet bullet1(textureb, speed1);
                    bullet1.settexture(btexture);
                    bullet1.sety(l);
                    gamebullets.push_back(bullet1);
                    j = 0;
                }

                if (c >= 300 and ccount < 3) {
                    sf::Vector2f cxy(getrandom(950, 200, player1.position().x), getrandom(650, 50, player1.position().y));
                    coin coin1(texturec, cxy);
                    gamecoins.push_back(coin1);
                    c = 0;
                    ccount++;
                }



                sf::Vector2f r(0, 0);
                player1.move(playerpath(player1, wx), m);

                if (m == 10) {
                    m = 0;
                }

                teleportcheck(player1, wx, wy);

                //int k;
                //if (p) {

                if (s == 60) {
                    sc++;
                    std::ostringstream points;
                    points << sc;
                    score.setString(A + points.str());
                    s = 0;
                }

                for (int i = 0; i < gamebullets.size(); i++) {
                    if (gamebullets[i].curbulletcoord() > 1010) {
                        gamebullets.erase(gamebullets.begin() + i);
                    }
                }

                for (int i = 0; i < gamebullets.size(); i++) {
                    //  gamebullets[i].scale();
                    gamebullets[i].move();
                    if (checkcollusion(gamebullets[i].getrec().getGlobalBounds(), player1.getrec().getGlobalBounds())) {
                        alive = false;
                        gamedeath.play();
                    }
                }
                for (int i = 0; i < gamecoins.size();i++) {
                    if (checkcollusion(gamecoins[i].getrec().getGlobalBounds(), player1.getrec().getGlobalBounds())) {
                        gamecoin.play();
                        gamecoins.erase(gamecoins.begin() + i);
                        ccount--;
                        sc += 5;
                        std::ostringstream points;
                        points << sc;
                        score.setString(A + points.str());

                    }
                }
            }
            if (alive == false and sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                break;
            }


            //gamebullets.resize(g);
            window.clear();
            window.draw(fieldspr);
            window.draw(player1.getsprite());
            window.draw(player1.getrec());
            for (int i = 0; i < gamecoins.size();i++) {
                coing.setPosition(gamecoins[i].position());
                window.draw(coing);
            }
            for (int i = 0; i < gamebullets.size(); i++) {
                //window.draw(gamebullets[i].getsprite());
                bul.setPosition(gamebullets[i].position());
                window.draw(bul);
                window.draw(gamebullets[i].getrec());
            }
            window.draw(lvltext);
            window.draw(score);
            if (pause) {
                window.draw(blackscreen);
                window.draw(ptext);
            }

            if (alive == false) {
                gametheme.stop();
                std::ofstream outbin("info.bin");
                std::ostringstream highpoints;
                if (highscore < sc) {
                    highscore = sc;
                    outbin.clear(0);
                    outbin.write((char*)&sc, sizeof(sc));
                   // inbin.read((char*)&sc, sizeof(sc));
                }
                else {
                    outbin.write((char*)&highscore, sizeof(highscore));
                }
                highpoints << highscore;
                outbin.close();
                htext.setString(H + highpoints.str());

                window.draw(blackscreen);
                window.draw(htext);
                window.draw(textlose);
            }
            //player1.getsprite().setPosition(sf::Vector2f(player1.getx(), player1.gety()));
           // window.draw(bullet1.getsprite());
            window.display();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::LostFocus and pause == false) {
                gametheme.pause();
                pause = true;
                pon.play();
            }
            if (event.type == sf::Event::Closed) {
                window.close();
                if (alive == true) {
                    std::ofstream outbin("info.bin");
                    outbin.write((char*)&highscore, sizeof(highscore));
                    outbin.close();
                }
            }   
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::M) {
                    if (mpressed == false) {
                        gametheme.setVolume(0);
                        gamedeath.setVolume(0);
                        gamecoin.setVolume(0);
                        gamelevel.setVolume(0);
                        mpressed = true;
                    }
                    else {
                        gametheme.setVolume(30);
                        gamedeath.setVolume(100);
                        gamecoin.setVolume(60);
                        gamelevel.setVolume(100);
                        mpressed = false;
                    }
                }
                if (event.key.code == sf::Keyboard::Escape and alive == true) {
                    if (!pause) {
                        gametheme.pause();
                        pause = true;
                        pon.play();
                    }
                    else { 
                        pause = false;
                        poff.play();
                        Sleep(100);
                        gametheme.play();
                    }

                }
            }

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            game = false;
        }
        }
        }
        while (game == false);

    return 0;
}