#pragma once

#include "Bar.h"
#include "Text.h"
#include <vector>
// Displays all non moving HUD components
class HUD {
    Text *fruitCollectedText;
    Text *fruitDroppedText;

    Bar *healthBar;
    Bar *energyBar;

    std::vector<Rect *> hudComponents;

    int fruitCollected;
    int fruitDropped;


  public:
    HUD();
    HUD(HUD &other);

    void increaseScore(int amount);
    
    void droppedFruit();

    void increaseHealth();
    void decreaseHealth();
    bool healthIsEmpty() const;

    void increaseEnergy();
    void decreaseEnergy();
    bool hasEnergy() const;

    
    void draw(float z = 0) const;

    ~HUD();
};
