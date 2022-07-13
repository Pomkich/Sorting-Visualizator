#pragma once
#include <vector>
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <functional>
#include <memory>
#include "AlgorithmObs.h"
#include <iostream>

class GraphicSort : public AlgorithmObs, public std::enable_shared_from_this<GraphicSort> {
private:
    sf::RenderWindow window;
    std::vector<int> sorting_elements;
    std::vector<sf::RectangleShape> graphic_elements;
    // sorting algorithms stored in fucntion object
    // all functions must have pointer to GraphicSort 
    // class (for notifying about each step of algorithm)
    // and reference to elements
    std::vector<std::function<void(std::shared_ptr<AlgorithmObs>, std::vector<int>&)>> sorting_algs;

public:
    GraphicSort();

    void Run();
    void RenderElements();

    void ShuffleElements();

    virtual void StepDone(int first, int second) override;
};