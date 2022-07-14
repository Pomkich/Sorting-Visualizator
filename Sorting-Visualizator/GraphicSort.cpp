#include "GraphicSort.h"

GraphicSort::GraphicSort() {
    alg_id = 0;
    elapsed_time = 0;
    ResizeElements(slow_elem_size);

    // setting text labels
    if (font.loadFromFile("tms.ttf")) {
        std::cout << "tms loaded" << std::endl;
    }
    alg_label.setFont(font);
    alg_label.setCharacterSize(40);
    alg_label.setPosition(0, 0);
    alg_label.setFillColor(sf::Color::Red);

    elem_label.setFont(font);
    elem_label.setCharacterSize(40);
    elem_label.setPosition(0, 50);
    elem_label.setFillColor(sf::Color::Red);

    time_label.setFont(font);
    time_label.setCharacterSize(40);
    time_label.setPosition(0, 100);
    time_label.setFillColor(sf::Color::Red);

    window.create(sf::VideoMode(window_width, window_height), "SFML works!");
}

void GraphicSort::Run() {
    alg_label.setString(alg_names[alg_id]);
    elem_label.setString("elements: " + std::to_string(sorting_elements.size()));
    time_label.setString("elapsed time: " + std::to_string(elapsed_time));
    RenderElements();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // shuffle elements
            else if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {
                // reset the time
                elapsed_time = 0;
                time_label.setString("elapsed time: " + std::to_string(elapsed_time));
                if (IsSlowAlgSelected()) {
                    ResizeElements(slow_elem_size);
                }
                else {
                    ResizeElements(elem_size);
                }
                ShuffleElements();
                RenderElements();
            }
            // start sorting
            else if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Right) {
                // reset the time
                elapsed_time = 0;
                time_label.setString("elapsed time: " + std::to_string(elapsed_time));
                // reset timer
                clock.restart();
                sorting_algs[alg_id](shared_from_this(), sorting_elements);
            }
            else if (event.type == sf::Event::TextEntered)  // algorithm choose
            {
                char temp = ' ';
                if (event.text.unicode < 128) {
                    temp = static_cast<char>(event.text.unicode);
                }

                if (temp >= '0' && temp < (sorting_algs.size() + '0')) {
                    // reset the time
                    elapsed_time = 0;
                    time_label.setString("elapsed time: " + std::to_string(elapsed_time));

                    alg_id = temp - '0';    // cast to int
                    alg_label.setString(alg_names[alg_id]);

                    if (IsSlowAlgSelected()) {
                        ResizeElements(slow_elem_size);
                    }
                    else {
                        ResizeElements(elem_size);
                    }

                    RenderElements();
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
    window.draw(alg_label);
    window.draw(elem_label);
    window.draw(time_label);
    window.display();
}

void GraphicSort::ResizeElements(int elem_sz) {
    sorting_elements.clear();
    graphic_elements.clear();
    sorting_elements.resize(elem_sz);
    graphic_elements.resize(elem_sz);
    rect_width = window_width / elem_sz;
    rect_height_scale = window_height / elem_sz;
    for (int i = 0; i < sorting_elements.size(); i++) {
        sorting_elements[i] = i + 1;
        graphic_elements[i].setSize(sf::Vector2f(rect_width, rect_height_scale * (i + 1)));
        graphic_elements[i].setPosition((i + 1) * rect_width, window_height);
        graphic_elements[i].rotate(180);
    }
    elem_label.setString("elements: " + std::to_string(sorting_elements.size()));
}

bool GraphicSort::IsSlowAlgSelected() {
    return slow_alghs.find(alg_names[alg_id]) != slow_alghs.end();
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

void GraphicSort::AddAlgorithm(void (*algh_ptr)(std::shared_ptr<AlgorithmObs>, std::vector<int>&), std::string alg_name, bool slow) {
    if (slow) {
        slow_alghs.insert(alg_name);
    }
    sorting_algs.push_back(algh_ptr);
    alg_names.push_back(alg_name);
}

void GraphicSort::StepDone(int first, int second) {
    
    graphic_elements[first].setSize(sf::Vector2f(rect_width, rect_height_scale * sorting_elements[first]));
    graphic_elements[second].setSize(sf::Vector2f(rect_width, rect_height_scale * sorting_elements[second]));
    graphic_elements[first].setFillColor(sf::Color::Red);
    graphic_elements[second].setFillColor(sf::Color::Red);
    RenderElements();
    graphic_elements[first].setFillColor(sf::Color::White);
    graphic_elements[second].setFillColor(sf::Color::White);
    elapsed_time += clock.getElapsedTime().asSeconds();
    clock.restart();
    time_label.setString("elapsed time: " + std::to_string(elapsed_time));
    //std::this_thread::sleep_for(std::chrono::milliseconds(1024));
}