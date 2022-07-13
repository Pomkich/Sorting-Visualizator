#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <iostream>
#include <vector>


using namespace std;

class GraphicWin {
private:
    sf::RenderWindow window;
    //sf::CircleShape cs;
    vector<int> sorting_elements;
    vector<sf::RectangleShape> graphic_elements;

public:
    GraphicWin() {
        sorting_elements.resize(elem_size);
        graphic_elements.resize(elem_size);
        for (int i = 0; i < sorting_elements.size(); i++) {
            sorting_elements[i] = i;
            graphic_elements[i].setSize(sf::Vector2f(rect_width, rect_height_scale * (i + 1)));
            graphic_elements[i].rotate(180);
            graphic_elements[i].setPosition((i + 1) * rect_width, window_height);
        }

        window.create(sf::VideoMode(window_width, window_height), "SFML works!");
    }

    void Run() {
        RenderElements();

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {

                }
            }
        }
    }

    void RenderElements() {
        window.clear();
        for (int i = 0; i < graphic_elements.size(); i++) {
            window.draw(graphic_elements[i]);
        }
        window.display();
    }

    void ShuffleElements() {

    }
};

int main()
{
    GraphicWin win;
    
    win.Run();

    return 0;
}