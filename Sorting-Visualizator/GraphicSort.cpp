#include "GraphicSort.h"

GraphicSort::GraphicSort() {
    alg_id = 0;
    sorting_elements.resize(elem_size);
    graphic_elements.resize(elem_size);
    for (int i = 0; i < sorting_elements.size(); i++) {
        sorting_elements[i] = i + 1;
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
            else if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Right) {
                sorting_algs[alg_id](shared_from_this(), sorting_elements);
            }
            else if (event.type == sf::Event::TextEntered)
            {
                char temp = ' ';
                if (event.text.unicode < 128) {
                    temp = static_cast<char>(event.text.unicode);
                }

                if (temp >= '0' && temp < (sorting_algs.size() + '0')) {
                    alg_id = temp - '0';    // cast to int
                    std::cout << alg_id << std::endl;
                }
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
        graphic_elements[i].setSize(sf::Vector2f(rect_width, rect_height_scale * sorting_elements[i]));
    }
}

void GraphicSort::AddAlgorithm(void (*algh_ptr)(std::shared_ptr<AlgorithmObs>, std::vector<int>&)) {
    sorting_algs.push_back(algh_ptr);
}

void GraphicSort::StepDone(int first, int second) {
    
    graphic_elements[first].setSize(sf::Vector2f(rect_width, rect_height_scale * sorting_elements[first]));
    graphic_elements[second].setSize(sf::Vector2f(rect_width, rect_height_scale * sorting_elements[second]));
    graphic_elements[first].setFillColor(sf::Color::Red);
    graphic_elements[second].setFillColor(sf::Color::Red);
    RenderElements();
    graphic_elements[first].setFillColor(sf::Color::White);
    graphic_elements[second].setFillColor(sf::Color::White);
    //std::this_thread::sleep_for(std::chrono::milliseconds(1024));
}