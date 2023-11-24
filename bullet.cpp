#include <SFML/Graphics.hpp>
#include <time.h>


class bullet {
	sf::Texture bullettexture;
	sf::Sprite bulletsprite;
	sf::Vector2f bulletcoord;
	sf::RectangleShape bulletrec;
	float speed;
public:
	bullet(){}
	bullet(std::string text, float speed1) {
		bullettexture.loadFromFile(text);
		bulletsprite.setScale(0.3, 0.3);
		//bullettexture = text;
		//bulletsprite.setTexture(bullettexture);
		//bulletcoord.y = getrandom(800, 0);
		bulletcoord.x = -200;
		speed = speed1;
		//------
		bulletsprite.setPosition(bulletcoord);
		bulletrec.setSize(sf::Vector2f(240*0.3, 80 * 0.3));
		bulletrec.setFillColor(sf::Color::Transparent);
		//bulletrec.setOutlineColor(sf::Color::Red);
		//bulletrec.setOutlineThickness(2);
		//---
		bulletrec.setPosition(bulletcoord);

	}
	void sety(float y1) {
		bulletcoord.y = y1;
	}

	sf::RectangleShape getrec() {
		return bulletrec;
	}


	void settexture(sf::Texture text) {
		bullettexture = text;
		bulletsprite.setTexture(text);
	}

	void setspeed(float speed1) {
		speed = speed1;
	}
	void move() {
		bulletcoord.x += speed;
		bulletrec.setPosition(bulletcoord);
		bulletsprite.setPosition(bulletcoord);
	}

	void spawn(const float ycor) {
		bulletcoord.y = ycor;
		bulletrec.setPosition(bulletcoord);
		bulletsprite.setPosition(bulletcoord);
	}
	sf::Sprite getsprite() {
		return bulletsprite;
	}
	float curbulletcoord(){
		return bulletcoord.x;
	}
	sf::Vector2f getcoor() {
		return bulletcoord;
	}

	void scale() {
		bulletsprite.setScale(0.3, 0.3);
	}


};