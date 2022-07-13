#include "GraphicSort.h"

GraphicSort::GraphicSort() {
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

void GraphicSort::Run() {
    RenderElements();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {
                ShuffleElements();
                RenderElements();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(32));
    }
}

void GraphicSort::RenderElements() {
    window.clear();
    for (int i = 0; i < graphic_elements.size(); i++) {
        window.draw(graphic_elements[i]);
    }
    window.display();
}

void GraphicSort::ShuffleElements() {
    srand(time(NULL));
    for (int i = 0; i < sorting_elements.size(); i++) {
        int switch_num = rand() % sorting_elements.size();
        std::swap(sorting_elements[i], sorting_elements[switch_num]);
    }
    for (int i = 0; i < graphic_elements.size(); i++) {
        graphic_elements[i].setSize(sf::Vector2f(rect_width, rect_height_scale * (sorting_elements[i] + 1)));
    }
}