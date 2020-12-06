#include "foo.h"

float rand_float(float min, float max)
{
    srand(time(0));
    return min + (rand() * (max - min)) / RAND_MAX;
}
bool Enemy::hitbox(float a, float b)
{
    if (a + 50.f >= getx() && a - 50.f <= getx() && b + 50.f >= gety() && b - 50.f <= gety()) {
        return true;
    }
    return false;
}
void Enemy::fallen(sf::RenderWindow& window)
{
    if (is_visible()) {
        sf::Texture tf;
        tf.loadFromFile("inf/rock.png");
        sf::Sprite aster;
        aster.setTexture(tf);
        aster.move(sf::Vector2f(getx(), gety()));
        window.draw(aster);
        if (getscore() == 0) {
            setx(getx() + gets());
        } else if (getscore() == 1) {
            setx(getx() - gets());
        }
        sety(gety() + rand_float(0.2, 0.8));
        if (getx() > G - 50.f) {
            sets(rand_float(0.5, 1)), setscore(1);
        } else if (getx() < 50.f) {
            sets(rand_float(0.5, 1)), setscore(0);
        }
        if (gety() > G)
            setvisible(false);
    }
}

void Hero::shut(int a, int b, sf::RenderWindow& window)
{
    if (getyb() > 0) {
        sf::Texture t;
        t.loadFromFile("inf/rail.png");
        sf::Sprite bullet;
        bullet.setTexture(t);
        bullet.move(sf::Vector2f(getxb(), getyb()));
        window.draw(bullet);
        setyb((getyb() - gets()));
        if (a + 52.f >= getxb() && a - 52.f <= getxb() && b + 52.f >= getyb() && b - 52.f <= getyb())
            setscore(getscore() + 1), setyb(0);
    } else {
        setyb(0);
    }
}
void Hero::move(sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right)
            setx(getx() + gets() - 0.2f);
        else if (event.key.code == sf::Keyboard::Left)
            setx(getx() - gets() + 0.2f);
        else if (event.key.code == sf::Keyboard::Space)
            if (getyb() == 0)
                setxb(getx() - 50), setyb(gety() - 100);
    }
    if (getx() > G - 50.f)
        setx(G - 50.f);
    else if (getx() < 50.f)
        setx(50.f);

    sf::Texture t;
    t.loadFromFile(img);
    sf::Sprite ship;
    ship.setTexture(t);
    ship.move(sf::Vector2f(getx() - 50.f, gety() - 100.f));
    window.draw(ship);
}
void Enemy::move(sf::Event& event, sf::RenderWindow& window)
{
    if (is_visible()) {
        srand(time(0));
        sf::Texture texture;
        texture.loadFromFile(getimg());
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.move(sf::Vector2f(getx() - 50.f, gety()));
        window.draw(sprite);
        if (getx() > G - 35.f)
            sets(gets() * (-1));
        else if (getx() < 25.f)
            sets(gets() * (-1));
        if (rand() % 1000 + 0 != 0)
            setx(getx() + gets());
    }
}