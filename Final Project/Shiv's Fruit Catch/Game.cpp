#include "Game.h"
#include <iostream>
#include <string>
#include <time.h>

static Game *singleton;
const float Game::PLAYER_BASE_SPEED = .02;

int frames = 0;
void frameCounter(int id) {
    std::cout << "FPS: " << frames << std::endl;
    frames = 0;
    glutTimerFunc(1000, frameCounter, id);
}

void gameLoop(int id) {
    singleton->player->idle();
    // singleton->explosion->setX(singleton->player->getX());
    // singleton->explosion->advance();

    // std::vector<MovingSprite *>::iterator end = singleton->objects.end();
    for (auto i = singleton->objects.begin(); i != singleton->objects.end();) {
        (*i)->idle();
        if ((*i)->getID() == fruit) {
            if (singleton->player->contains((*i)->getX(), (*i)->getY())) {
                singleton->score++;
                singleton->s->setText("Score: " + std::to_string(singleton->score));

                delete (*i);
                i = singleton->objects.erase(i);
            } else if ((*i)->getY() < -1.5) {
                delete (*i);
                i = singleton->objects.erase(i);
            } else {
                ++i;
            }
        }
    }

    // singleton->objects.erase(toBeDeleted);

    glutPostRedisplay();
    frames++;

    // std::cout << singleton->score << std::endl;

    glutTimerFunc(1000.0 / 60, gameLoop, id);
    // glutTimerFunc(1000, gameLoop, id);
}

void spawnFruit(int id) {
    singleton->createFruit();
    glutTimerFunc(1000, spawnFruit, id);
}

void Game::createFruit() {
    srand(time(NULL));

    float fruitX = (rand() % 190) / 100.0 - 1.0;
    
    switch (rand() % 3) {
    case 0:
        objects.push_back(new MovingSprite("apple.png", 1, 1, fruitX, 1, .1, .1, 0, -.01, fruit));
        break;
    case 1:
        objects.push_back(new MovingSprite("banana.png", 1, 1, fruitX, 1, .1, .1, 0, -.01, fruit));
        break;
    case 2:
        objects.push_back(new MovingSprite("mango.png", 1, 1, fruitX, 1, .1, .1, 0, -.01, fruit));
    }
}

Game::Game() {
    score = 0;
    // explosion = new Sprite("explosion.png", 5, 5, -0.8, 0.8, 0.25, 0.25);
    player = new Player();

    s = new Text(0, 0, "score: 0", 0, 0, 1);

    // shapes.push_back(explosion);
    singleton = this;

    gameLoop(0);
    spawnFruit(2);

    // prints fps of the game every second
    frameCounter(1);
}

void Game::idle() {
}

void Game::keyDown(unsigned char key, float x, float y) {
    if (key == 'a' || key == 'A') {
        player->setDX(player->getDX() - PLAYER_BASE_SPEED);
        player->setDirection(1);

    } else if (key == 'd' || key == 'D') {

        player->setDX(player->getDX() + PLAYER_BASE_SPEED);
        player->setDirection(0);

    } else if (key == 'w' || key == 'W') {
        player->jump();
    }

    std::cout << key << std::endl;
}

void Game::keyUp(unsigned char key, float x, float y) {
    if (key == 'a' || key == 'A') {
        player->setDX(player->getDX() + PLAYER_BASE_SPEED);
        // std::cout << player->getDX() << std::endl;

    } else if (key == 'd' || key == 'D') {
        player->setDX(player->getDX() - PLAYER_BASE_SPEED);
    }
    // std::cout<< key << std::endl;
}

void Game::specialKeyDown(int key, float x, float y) {
    if (key == GLUT_KEY_SHIFT_L) {
        player->setIsFaster(true);
    }
}

void Game::specialKeyUp(int key, float x, float y) {
    if (key == GLUT_KEY_SHIFT_L) {
        player->setIsFaster(false);
    }
}

void Game::draw() const {
    player->draw();
    s->draw(1);
    for (auto i = objects.begin(); i != objects.end(); i++) {
        (*i)->draw();
    }
    for (auto i = hud.begin(); i != hud.end(); i++) {
        (*i)->draw();
    }
}

Game::~Game() {
    for (auto i = objects.begin(); i != objects.end(); i++) {
        delete *i;
    }
    for (auto i = hud.begin(); i != hud.end(); i++) {
        delete *i;
    }
    delete player;
}