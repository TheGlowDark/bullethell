#include <SFML/Graphics.hpp>


class model {
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f coord;
	sf::RectangleShape rec;
public:
	sf::Vector2f position() {
		return(coord);
	}
	sf::Sprite getsprite() {
		return sprite;
	}
	void setx(float x1) {
		coord.x = x1;
		sprite.setPosition(coord);
	}
	void sety(float y1) {
		coord.y = y1;
		sprite.setPosition(coord);
	}
	sf::RectangleShape getrec() {
		return rec;
	}

};


class coin :public model {
public:
	coin() {}
	coin(std::string text, sf::Vector2f coincoor){
		texture.loadFromFile(text);
		sprite.setTexture(texture);
		//sprite.setScale(0.3, 0.3);
		rec.setSize(sf::Vector2f(192 * 0.3, 256 * 0.3));
		coord = coincoor;
		sprite.setPosition(coord);
		rec.setPosition(coord);
	}
};





class player:public model {
	short int health = 3;
	sf::Texture playerstanding;
	sf::Texture playertexturerunleft;
	sf::Texture playertexturerunright;
	sf::Vector2f psize;
	sf::Vector2f reccor;
public:
	player() {

	}
	~player() {

	}

	player(sf::Vector2f v, std::string texture_name, std::string texture_name1, std::string texture_name2) {
		playertexturerunleft.loadFromFile(texture_name);
		playertexturerunright.loadFromFile(texture_name1);
		playerstanding.loadFromFile(texture_name2);
	    sprite.setTexture(playerstanding);
		sprite.setScale(0.2, 0.2); //120 120
		//---------
		sf::Vector2f r(600 * 0.2 - 60, 600 * 0.2 - 43);
		psize = r;

		rec.setSize(psize);
		rec.setFillColor(sf::Color::Transparent);
	//	playerrec.setOutlineColor(sf::Color::Red);
		//playerrec.setOutlineThickness(2);
		//----------

		coord = v;
		reccor.x = coord.x + 20;
		reccor.y = coord.y + 20;
		rec.setPosition(reccor);

	}

	void move(sf::Vector2f xy, int y) { //y - tick
		if (y == 10) {
			sprite.setTexture(playertexturerunleft);
		}
		else if(y == 5)
			sprite.setTexture(playertexturerunright);
		coord = sprite.getPosition() + xy;
	//--------------------------
		//if (xy.x > 0) {
		//	sprite.setTexture();
		//}
		//if (xy.x < 0) {
		//	sprite.setTexture()
		//}

		reccor.x = coord.x + 20;
		reccor.y = coord.y + 23;

		rec.setPosition(reccor);

		sprite.setPosition(coord);
	}


	void getstart() {
		coord.x = 500;
		coord.y = 400;
		reccor.x = coord.x;
		reccor.y = coord.y + 20;
		rec.setPosition(reccor);
		sprite.setPosition(coord);
	}
};



#include <time.h>


class bullet:public model {
	float speed;
public:
	bullet() {}
	bullet(std::string text, float speed1) {
		texture.loadFromFile(text);
		sprite.setScale(0.3, 0.3);
		//bullettexture = text;
		//bulletsprite.setTexture(bullettexture);
		//bulletcoord.y = getrandom(800, 0);
		coord.x = -200;
		speed = speed1;
		//------
		sprite.setPosition(coord);
		rec.setSize(sf::Vector2f(240 * 0.3, 80 * 0.3));
		rec.setFillColor(sf::Color::Transparent);
		//bulletrec.setOutlineColor(sf::Color::Red);
		//bulletrec.setOutlineThickness(2);
		//---
		rec.setPosition(coord);

	}

	void settexture(sf::Texture text) {
		texture = text;
		sprite.setTexture(text);
	}

	void setspeed(float speed1) {
		speed = speed1;
	}
	void move() {
		coord.x += speed;
		rec.setPosition(coord);
		sprite.setPosition(coord);
	}

	void spawn(const float ycor) {
		coord.y = ycor;
		rec.setPosition(coord);
		sprite.setPosition(coord);
	}

	float curbulletcoord() {
		return coord.x;
	}

	void scale() {
		sprite.setScale(0.3, 0.3);
	}


};



