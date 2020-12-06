#include "foo.h"

int main()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(SIDE, SIDE), "StarFighter");
    sf::Event event;

    Hero* dinam[2];
    dinam[0] = new Hero;
    dinam[1] = new Enemy;
    Enemy astr[3];

    for (int i = 0; i < 3; i++)
        astr[i].setvisible(false);

    sf::Font font;
    font.loadFromFile("inf/arial.ttf");
    sf::Text text, txtlive;
    text.setFont(font);
    txtlive.setFont(font);
    text.setCharacterSize(45);
    txtlive.setCharacterSize(25);

    int lives = 3, timeout = 0;
    int temp = 0, is_game = 0;

    sf::Texture back;
    back.loadFromFile("inf/back.png");
    sf::Sprite background(back);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (is_game)
                        timeout = 1, is_game = 0;
                } else if (event.key.code == sf::Keyboard::Enter) {
                    if (is_game == 0 && timeout == 0)
                        lives = 3, is_game = 1, dinam[0]->setscore(0);
                    else if (timeout)
                        timeout = 0, is_game = 1;
                }
            }
        }
        window.clear();
        window.draw(background);
        if (is_game) {
            text.setString("Score: " + std::to_string(dinam[0]->getscore()));
            text.setPosition(0, 0);
            window.draw(text);

            sf::Texture hs;
            hs.loadFromFile("inf/health.png");
            sf::Sprite hearts[3];

            for (int i = 0; i < lives; i++) {
                hearts[i].setTexture(hs);
                hearts[i].move(sf::Vector2f(700 - i * 50.f, 0));
                window.draw(hearts[i]);
            }

            temp = dinam[0]->getscore();
            if (dinam[1]->is_visible())
                dinam[1]->move(event, window);
            dinam[0]->move(event, window);
            dinam[0]->shut(dinam[1]->getx(), dinam[1]->gety(), window);
            dinam[0]->swap();
            if (temp != dinam[0]->getscore()) {
                dinam[1]->swap();
                dinam[1]->setvisible(false);
            }
            if (dinam[1]->is_visible() == false) {
                if (astr[0].is_visible() == false && astr[1].is_visible() == false && astr[2].is_visible() == false) {
                    for (int i = 0; i < 3; i++) {
                        astr[i].setx(dinam[1]->getx());
                        astr[i].sety(dinam[1]->gety());
                        astr[i].sets(rand_float(0.2, 0.8));
                    }
                    astr[0].setvisible(true), astr[1].setvisible(true), astr[2].setvisible(true);
                    astr[0].setscore(0), astr[1].setscore(1), astr[2].setscore(2);
                }
                for (int i = 0; i < 3; i++) {
                    if (astr[i].is_visible() == true)
                        astr[i].fallen(window);
                }
                if (astr[0].hitbox(dinam[0]->getx(), dinam[0]->gety()) || astr[1].hitbox(dinam[0]->getx(), dinam[0]->gety()) || astr[2].hitbox(dinam[0]->getx(), dinam[0]->gety())) {
                    astr[0].setvisible(false);
                    astr[1].setvisible(false);
                    astr[2].setvisible(false);
                    dinam[1]->setvisible(true);
                    lives -= 1;
                }
                if (astr[0].is_visible() == false && astr[1].is_visible() == false && astr[2].is_visible() == false) {
                    dinam[1]->setvisible(true);
                }
                if (lives == 0) {
                    is_game = 0;
                }
            }
        } else {
            text.setString("Press Enter for play!");
            text.setPosition(200, 350);
            window.draw(text);
            if (timeout) {
                txtlive.setString("Your Lives: " + std::to_string(lives));
                txtlive.setPosition(350, 410);
                window.draw(txtlive);
            } else if (!timeout && lives == 0) {
                txtlive.setString("Your score: " + std::to_string(dinam[0]->getscore()));
                txtlive.setPosition(350, 410);
                window.draw(txtlive);
            }
        }
        window.display();
    }
    return 0;
}
