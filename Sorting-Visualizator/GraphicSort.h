#pragma once
#include <vector>
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <thread>

class GraphicSort {
private:
    sf::RenderWindow window;
    std::vector<int> sorting_elements;
    std::vector<sf::RectangleShape> graphic_elements;

public:
    GraphicSort();

    void Run();
    void RenderElements();

    void ShuffleElements();
};