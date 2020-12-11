#ifndef FOO_H
#define FOO_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using std::cin;
using std::cout;
using std::endl;

#define G 800
#define SIDE 800

class Object {
private:
    float x, y, speed;

public:
    void setx(float a) { x = a; }
    void sety(float a) { y = a; }
    void sets(float a) { speed = a; }
    float getx() { return x; }
    float gety() { return y; }
    float gets() { return speed; }

    virtual void move(sf::Event& event, sf::RenderWindow& window) = 0;
    virtual void swap() = 0;
};

class Hero : public Object {
private:
    int score;
    std::string img;
    float x_for_bullet;
    float y_for_bullet;
    bool visible;

public:
    Hero(float ox = 400.f, float oy = 770.f, float osp = 0.3f)
        : score(0)
        , img("inf/ship.png")
        , x_for_bullet(0)
        , y_for_bullet(0)
    {
        setx(ox), sety(oy), sets(osp);
    }
    float getxb() { return x_for_bullet; }
    void setxb(float a) { x_for_bullet = a; }
    float getyb() { return y_for_bullet; }
    void setyb(float a) { y_for_bullet = a; }
    void setscore(int a) { score = a; }
    int getscore() { return score; }
    void setimg(std::string a) { img = a; }
    std::string getimg() { return img; }
    bool is_visible() { return visible; }
    void setvisible(bool a) { visible = a; }
    void move(sf::Event& event, sf::RenderWindow& window);
    void shut(int a, int b, sf::RenderWindow& window);
    void swap()
    {
        if (img == "inf/ship.png")
            img = "inf/ship2.png";
        else
            img = "inf/ship.png";
    }
};

class Enemy : public Hero {
public:
    Enemy(float ox, float oy, float osp)
    {
        setimg("inf/planet1.png"), setvisible(true), setx(ox), sety(oy), sets(osp);
    }
    Enemy(float ox = 400.f, float oy = 60.f)
    {
        setimg("inf/planet2.png"), setvisible(true), setx(ox), sety(oy), sets(0.1f);
    }
    Enemy(float ox, float oy, std::string oimg)
    {
        setimg(oimg), setvisible(true), setx(ox), sety(oy), sets(0.13f);
    }
    bool hitbox(float a, float b);

    void fallen(sf::RenderWindow& window);
    void move(sf::Event& event, sf::RenderWindow& window);
    void swap()
    {
        if (getimg() == "inf/planet1.png")
            setimg("inf/planet2.png");
        else if (getimg() == "inf/planet2.png")
            setimg("inf/planet3.png");
        else
            setimg("inf/planet1.png");
    }
};
float rand_float(float min, float max);
#endif